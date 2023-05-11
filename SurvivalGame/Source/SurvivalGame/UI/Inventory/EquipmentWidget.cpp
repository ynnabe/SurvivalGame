// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"

#include "InventoryGridWidget.h"

void UEquipmentWidget::OnSetEquipment(USGInventoryComponent* InventoryComponent, FVector2d& FinishSize)
{
	FVector2d TempFinishSize;
	GridWidget->InitializeGrid(InventoryComponent, TempFinishSize);
	FinishSize = TempFinishSize;
}
