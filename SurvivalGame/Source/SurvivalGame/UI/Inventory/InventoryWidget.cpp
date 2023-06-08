// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "EquipmentWidget.h"
#include "Blueprint/DragDropOperation.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "SurvivalGame/Inventory/InventoryItem.h"
#include "SurvivalGame/Inventory/Equipment/EquipmentItem.h"

bool UInventoryWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UInventoryItem* Payload = Cast<UInventoryItem>(InOperation->Payload);
	Payload->Rotate();
	Payload->ReturnBack();

	return true;
}

void UInventoryWidget::SetTorsoEquipmentWidget(UEquipmentItem* NewEquipment)
{
	FVector2d FinishSize;
	TorsoEquipmentWidget->OnSetEquipment(NewEquipment, FinishSize);

	UCanvasPanelSlot* TorsoEquipmentWidgetAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TorsoEquipmentWidget);
	FVector2d CurrentSize = TorsoEquipmentWidgetAsCanvasSlot->GetSize();
	TorsoEquipmentWidgetAsCanvasSlot->SetSize(FVector2d(CurrentSize.X, FinishSize.Y));
}

void UInventoryWidget::SetBackpackEquipmentWidget(UEquipmentItem* NewEquipment)
{
	FVector2d FinishSize;
	BackpackEquipmentWidget->OnSetEquipment(NewEquipment, FinishSize);

	UCanvasPanelSlot* BackpackEquipmentWidgetAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(BackpackEquipmentWidget);
	FVector2d CurrentSize = BackpackEquipmentWidgetAsCanvasSlot->GetSize();
	BackpackEquipmentWidgetAsCanvasSlot->SetSize(FVector2d(CurrentSize.X, FinishSize.Y));
}
