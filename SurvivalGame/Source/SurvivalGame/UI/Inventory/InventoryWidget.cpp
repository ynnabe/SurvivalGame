// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryWidget.h"

#include "EquipmentWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UInventoryWidget::SetTorsoEquipmentWidget(USGInventoryComponent* InventoryComponent)
{
	FVector2d FinishSize;
	TorsoEquipmentWidget->OnSetEquipment(InventoryComponent, FinishSize);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Finish size: X: %f Y: %f"), FinishSize.X, FinishSize.Y));

	UCanvasPanelSlot* TorsoEquipmentWidgetAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(TorsoEquipmentWidget);
	FVector2d CurrentSize = TorsoEquipmentWidgetAsCanvasSlot->GetSize();
	TorsoEquipmentWidgetAsCanvasSlot->SetSize(FVector2d(CurrentSize.X, FinishSize.Y));
}

void UInventoryWidget::SetBackpackEquipmentWidget(USGInventoryComponent* InventoryComponent)
{
	FVector2d FinishSize;
	BackpackEquipmentWidget->OnSetEquipment(InventoryComponent, FinishSize);

	UCanvasPanelSlot* BackpackEquipmentWidgetAsCanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(BackpackEquipmentWidget);
	FVector2d CurrentSize = BackpackEquipmentWidgetAsCanvasSlot->GetSize();
	BackpackEquipmentWidgetAsCanvasSlot->SetSize(FVector2d(CurrentSize.X, FinishSize.Y));
}
