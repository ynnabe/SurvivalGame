// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"

#include "EquipmentWidget.h"
#include "ItemWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetMathLibrary.h"
#include "SurvivalGame/Character/SGPlayerCharacter.h"
#include "SurvivalGame/Character/Controller/SGPlayerController.h"
#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"
#include "SurvivalGame/Inventory/InventoryItem.h"

void UInventoryGridWidget::InitializeGrid(USGInventoryComponent* InventoryComponent, FVector2d& FinishSize)
{
	CachedInventoryComponent = InventoryComponent;
	UCanvasPanelSlot* GridBorderAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridBorder);
	FVector2d NewSize = FVector2d(CachedInventoryComponent->GetColumns() * TileSize, CachedInventoryComponent->GetRows() * TileSize);
	FinishSize = NewSize;
	GridBorderAsCanvasSlot->SetSize(NewSize);

	CreateLineSegments();
	Refresh();

	CachedInventoryComponent->OnInventoryChanged.BindUObject(this, &UInventoryGridWidget::Refresh);

	Player = Cast<ASGPlayerCharacter>(GetOwningPlayerPawn());
	PlayerController = Cast<ASGPlayerController>(Player->GetController());
}

void UInventoryGridWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}

bool UInventoryGridWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                        UDragDropOperation* InOperation)
{
	UInventoryItem* Payload = GetPayload(InOperation);
	if(IsRoomAvailableForPayload(Payload))
	{
		FInventoryTile Tile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y);
		int32 Index = CachedInventoryComponent->TileToIndex(&Tile);
		CachedInventoryComponent->AddItem(Payload, Index);
		DrawDropLocation = false;
		return true;
	}
	if(CachedInventoryComponent->TryAddItem(Payload))
	{
		DrawDropLocation = false;
		return true;
	}

	Payload->ReturnBack();
	DrawDropLocation = false;
	return true;
}

bool UInventoryGridWidget::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	FVector2D MousePositionAbsolute = InDragDropEvent.GetScreenSpacePosition();
	FVector2D MousePositionLocal = InGeometry.AbsoluteToLocal(MousePositionAbsolute);

	bool Right;
	bool Down;
	MousePositionInTile(MousePositionLocal, Right, Down);

	UInventoryItem* Payload = Cast<UInventoryItem>(InOperation->Payload);
	FIntPoint ItemDimension = Payload->GetItemDimensions();

	int32 RightInt;
	int32 DownInt;

	if(Right)
	{
		RightInt = UKismetMathLibrary::Clamp(ItemDimension.X - 1, 0, ItemDimension.X - 1);
	}
	else
	{
		RightInt = UKismetMathLibrary::Clamp(ItemDimension.X, 0, ItemDimension.X);
	}

	if(Down)
	{
		DownInt = UKismetMathLibrary::Clamp(ItemDimension.Y - 1, 0, ItemDimension.Y - 1);
	}
	else
	{
		DownInt = UKismetMathLibrary::Clamp(ItemDimension.Y, 0, ItemDimension.Y);
	}

	FIntPoint RawLocation(RightInt, DownInt);
	FIntPoint Location = RawLocation / 2;

	FVector2d MouseLocationTileSize = MousePositionLocal / TileSize;
	
	DraggedItemTopLeftTile = FIntPoint(UKismetMathLibrary::FTrunc(MouseLocationTileSize.X), UKismetMathLibrary::FTrunc(MouseLocationTileSize.Y)) - Location;

	return true;
}

void UInventoryGridWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	DrawDropLocation = true;
}

void UInventoryGridWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	DrawDropLocation = false;
}

FReply UInventoryGridWidget::NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if(InKeyEvent.GetKey() == EKeys::R)
	{
		UInventoryItem* Payload = GetPayload(UWidgetBlueprintLibrary::GetDragDroppingContent());
		if(IsValid(Payload))
		{
			Payload->Rotate();
			UItemWidget* ItemWidget = Cast<UItemWidget>(UWidgetBlueprintLibrary::GetDragDroppingContent()->DefaultDragVisual);
			ItemWidget->Refresh();

			return FReply::Handled(); 
		}
	}

	return FReply::Handled();
}

FReply UInventoryGridWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		PlayerController->ClearWidgets();
		FEventReply Reply;
		return Reply.NativeReply;
	}

	FEventReply Reply;
	return Reply.NativeReply;
}

int32 UInventoryGridWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                        const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                        const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	for (auto Line : Lines)
	{
		FVector2d LocalTopLeft = USlateBlueprintLibrary::GetLocalTopLeft(GridBorder->GetCachedGeometry());
		FVector2d PositionA = Line.StartPoint + LocalTopLeft;
		FVector2d PositionB = Line.EndPoint + LocalTopLeft;
		FPaintContext PaintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
		UWidgetBlueprintLibrary::DrawLine(PaintContext, PositionA, PositionB, FLinearColor::White, true, 1.0f);
	}

	if(UWidgetBlueprintLibrary::IsDragDropping() && DrawDropLocation)
	{
		UInventoryItem* Payload = GetPayload(UWidgetBlueprintLibrary::GetDragDroppingContent());
		if(IsRoomAvailableForPayload(Payload))
		{
			FPaintContext PaintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
			FVector2d Position = UKismetMathLibrary::Conv_IntPointToVector2D(DraggedItemTopLeftTile) * TileSize;
			FVector2d Size = FVector2d(Payload->GetItemDimensions().X * TileSize, Payload->GetItemDimensions().Y * TileSize);
			UWidgetBlueprintLibrary::DrawBox(PaintContext, Position, Size, SlateBrush, AvailableColor);
		}
		else
		{
			FPaintContext PaintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
			FVector2d Position = UKismetMathLibrary::Conv_IntPointToVector2D(DraggedItemTopLeftTile) * TileSize;
			FVector2d Size = FVector2d(Payload->GetItemDimensions().X * TileSize, Payload->GetItemDimensions().Y * TileSize);
			UWidgetBlueprintLibrary::DrawBox(PaintContext, Position, Size, SlateBrush, NotAvailableColor);
		}
	}
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UInventoryGridWidget::MousePositionInTile(FVector2d MousePosition, bool& Right, bool& Down) const
{
	Right = FMath::Fmod(MousePosition.X, TileSize) > TileSize / 2.0f;
	Down = FMath::Fmod(MousePosition.Y, TileSize) > TileSize / 2.0f;
}

bool UInventoryGridWidget::IsRoomAvailableForPayload(UInventoryItem* Payload) const
{
	if(IsValid(Payload))
	{
		FInventoryTile Tile(DraggedItemTopLeftTile.X, DraggedItemTopLeftTile.Y);
		int32 TopLeftIndex = CachedInventoryComponent->TileToIndex(&Tile);
		if(CachedInventoryComponent->IsRoomAvailable(Payload, TopLeftIndex))
		{
			return true;
		}

		return false;
	}

	return false;
}

UInventoryItem* UInventoryGridWidget::GetPayload(UDragDropOperation* DragDropOperation) const
{
	if(!IsValid(DragDropOperation))
	{
		return nullptr;
	}

	UInventoryItem* Payload = Cast<UInventoryItem>(DragDropOperation->Payload);
	return Payload;
}

void UInventoryGridWidget::OnItemRemoved(UInventoryItem* ItemToRemove, bool bNeedToDrop)
{
	CachedInventoryComponent->RemoveItem(ItemToRemove, bNeedToDrop);
	Refresh();
}

void UInventoryGridWidget::CreateLineSegments()
{
	for(int VerticalLine = 0; VerticalLine <= CachedInventoryComponent->GetColumns(); VerticalLine++)
	{
		int X = VerticalLine * TileSize;
		FVector2d StartLine = FVector2d(X, 0.0f);
		FVector2d EndLine = FVector2d(X, CachedInventoryComponent->GetRows() * TileSize);
		FGridLine GridLine(StartLine, EndLine);
		Lines.Add(GridLine);
	}

	for(int HorizontalLine = 0; HorizontalLine <= CachedInventoryComponent->GetRows(); HorizontalLine++)
	{
		int Y = HorizontalLine * TileSize;
		FVector2d StartLine = FVector2d(0.0f, Y);
		FVector2d EndLine = FVector2d(CachedInventoryComponent->GetColumns() * TileSize, Y);
		FGridLine GridLine(StartLine, EndLine);
		Lines.Add(GridLine);
	}
}

void UInventoryGridWidget::Refresh()
{
	GridCanvasPanel->ClearChildren();

	TMap<UInventoryItem*, FInventoryTile> ItemsMap = CachedInventoryComponent->GetItemsAsMap();

	for (const auto ItemMap : ItemsMap)
	{
		UItemWidget* CurrentItemWidget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemWidgetClass);
		CurrentItemWidget->SetItem(ItemMap.Key);
		CurrentItemWidget->SetTileSize(TileSize);
		CurrentItemWidget->OnRemoved.AddUObject(this, &UInventoryGridWidget::OnItemRemoved);
		UCanvasPanelSlot* ItemWidgetAsCanvasSlot = Cast<UCanvasPanelSlot>(GridCanvasPanel->AddChild(CurrentItemWidget));
		ItemWidgetAsCanvasSlot->SetAutoSize(true);
		FVector2d NewPosition = FVector2d(ItemMap.Value.X * TileSize - 5.0f, ItemMap.Value.Y * TileSize - 4.0f);
		ItemWidgetAsCanvasSlot->SetPosition(NewPosition);
	}
}
