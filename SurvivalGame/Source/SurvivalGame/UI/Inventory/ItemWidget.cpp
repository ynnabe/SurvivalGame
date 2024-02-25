// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

#include "InventoryGridWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "ContextItem/ItemContextWidget.h"
#include "SurvivalGame/Actors/Items/Item.h"
#include "SurvivalGame/Character/SGPlayerCharacter.h"
#include "SurvivalGame/Character/Controller/SGPlayerController.h"
#include "SurvivalGame/Inventory/InventoryItem.h"

void UItemWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	BackgroundBorder->SetBrushColor(HoverColor);
}

void UItemWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	BackgroundBorder->SetBrushColor(UnhoverColor);
}

FReply UItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if(InMouseEvent.IsMouseButtonDown(EKeys::RightMouseButton))
	{
		UItemContextWidget* ContextWidget = CreateWidget<UItemContextWidget>(GetOwningPlayer(), ItemContextClass);
		ContextWidget->AddToViewport();
		ContextWidget->SetItem(Item, this);
		PlayerController->SetItemContextWidget(ContextWidget);
		float MousePositionX;
		float MousePositionY;
		PlayerController->GetMousePosition(MousePositionX, MousePositionY);
		FVector2d MousePosition2D = FVector2d(MousePositionX, MousePositionY);
		ContextWidget->SetPositionInViewport(MousePosition2D);
		
		FEventReply Reply;
		return Reply.NativeReply;
	}
	
	PlayerController->ClearWidgets();
	
	FEventReply Reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	return Reply.NativeReply;
}

void UItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                       UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UDragDropOperation* DragDropOperation = Cast<UDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass()));

	DragDropOperation->Payload = Item;
	DragDropOperation->DefaultDragVisual = this;

	OnRemoved.Broadcast(Item, false);

	RemoveFromParent();

	OutOperation = DragDropOperation;
	PlaySound(DragSound);
}

void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetWorld()->GetTimerManager().SetTimer(InitializeTimerHandle, [=]()
	{
		Refresh();
	}, 0.001f, false);

	Player = Cast<ASGPlayerCharacter>(GetOwningPlayerPawn());
	PlayerController = Cast<ASGPlayerController>(Player->GetController());
}

void UItemWidget::Refresh()
{
	FIntPoint Dimensions = Item->GetItemDimensions();

	Size = FVector2d(Dimensions.X * TileSize, Dimensions.Y * TileSize);

	BackgroundSizeBox->SetWidthOverride(Size.X);
	BackgroundSizeBox->SetHeightOverride(Size.Y);
	UCanvasPanelSlot* ItemIconAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(Cast<UWidget>(ItemIcon));

	ItemIconAsCanvasSlot->SetSize(Size);
	SetItemIcon();
}

void UItemWidget::SetItemIcon()
{
	UMaterialInterface* ItemIconMaterial = Item->GetItemIcon();

	FSlateBrush Brush = UWidgetBlueprintLibrary::MakeBrushFromMaterial(ItemIconMaterial, Size.X, Size.Y);
	
	ItemIcon->SetBrush(Brush);
	
}

void UItemWidget::SetItem(UInventoryItem* ItemIn)
{
	Item = ItemIn;
}

void UItemWidget::SetTileSize(float TileSizeIn)
{
	TileSize = TileSizeIn;
}

void UItemWidget::SetOwnerGridWidget(UInventoryGridWidget* OwnerGrid)
{
	OwnerGridWidget = OwnerGrid;
}

void UItemWidget::RemoveItem()
{
	OnRemoved.Broadcast(Item, true);
}
