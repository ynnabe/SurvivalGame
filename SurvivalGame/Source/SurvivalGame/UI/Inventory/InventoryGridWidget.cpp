// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryGridWidget.h"

#include "EquipmentWidget.h"
#include "ItemWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Border.h"
#include "Components/CanvasPanelSlot.h"
#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"

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
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UInventoryGridWidget::OnItemRemoved(AItem* ItemToRemove)
{
	CachedInventoryComponent->RemoveItem(ItemToRemove);
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

	TMap<AItem*, FInventoryTile> ItemsMap = CachedInventoryComponent->GetItemsAsMap();

	for (auto ItemMap : ItemsMap)
	{
		UItemWidget* CurrentItemWidget = CreateWidget<UItemWidget>(GetOwningPlayer(), ItemWidgetClass);
		CurrentItemWidget->SetItem(ItemMap.Key);
		CurrentItemWidget->SetTileSize(TileSize);
		CurrentItemWidget->OnRemoved.BindUObject(this, &UInventoryGridWidget::OnItemRemoved);
		UCanvasPanelSlot* ItemWidgetAsCanvasSlot = Cast<UCanvasPanelSlot>(GridCanvasPanel->AddChild(CurrentItemWidget));
		ItemWidgetAsCanvasSlot->SetAutoSize(true);
		FVector2d NewPosition = FVector2d(ItemMap.Value.X * TileSize, ItemMap.Value.Y * TileSize);
		ItemWidgetAsCanvasSlot->SetPosition(NewPosition);
	}
}
