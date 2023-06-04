// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemWidget.h"

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
#include "SurvivalGame/Actors/Items/Item.h"
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

	OnRemoved.Execute(Item);

	RemoveFromParent();

	OutOperation = DragDropOperation;
}

void UItemWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	GetWorld()->GetTimerManager().SetTimer(InitializeTimerHandle, [=]()
	{
		Refresh();
	}, 0.001f, false);
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
