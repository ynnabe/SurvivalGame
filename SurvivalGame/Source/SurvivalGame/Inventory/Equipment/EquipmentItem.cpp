// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentItem.h"

#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"

UEquipmentItem::UEquipmentItem()
{
	InventoryComponent = CreateDefaultSubobject<USGInventoryComponent>(TEXT("InventoryComponent"));
}

void UEquipmentItem::Initialize(FText NameIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageRotatedIn,
                                FIntPoint ItemDimensionsIn, USGInventoryComponent* InventoryComponentIn, EEquipmentType TypeIn)
{
	Name = NameIn;
	Image = ImageIn;
	ImageRotated = ImageRotatedIn;
	ItemDimensions = ItemDimensionsIn;
	Type = TypeIn;
	InventoryComponent->SetCapacity(InventoryComponentIn->GetColumns(), InventoryComponentIn->GetRows());
	InventoryComponent->SetItems(InventoryComponentIn->GetItems());
}
