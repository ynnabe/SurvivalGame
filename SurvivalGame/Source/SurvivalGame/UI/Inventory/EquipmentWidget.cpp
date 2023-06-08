// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"

#include "InventoryGridWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "SurvivalGame/Inventory/Equipment/EquipmentItem.h"

void UEquipmentWidget::OnSetEquipment(UEquipmentItem* NewEquipment, FVector2d& FinishSize)
{
	FVector2d TempFinishSize;
	GridWidget->InitializeGrid(NewEquipment->GetInventoryComponent(), TempFinishSize);
	GridWidget->SetVisibility(ESlateVisibility::Visible);
	FinishSize = TempFinishSize;
	
	EquipmentName->SetText(NewEquipment->GetItemName());
	UMaterialInterface* ItemImageMaterial = NewEquipment->GetItemImage();
	FSlateBrush Brush = UWidgetBlueprintLibrary::MakeBrushFromMaterial(ItemImageMaterial);
	EquipmentImage->SetBrush(Brush);
}
