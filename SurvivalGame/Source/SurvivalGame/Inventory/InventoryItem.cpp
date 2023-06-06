// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"

void UInventoryItem::Initialize(FText NameIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageRotatedIn,
                                FIntPoint ItemDimensionsIn)
{
	Name = NameIn;
	Image = ImageIn;
	ImageRotated = ImageRotatedIn;
	ItemDimensions = ItemDimensionsIn;
}

void UInventoryItem::Initialize(FText NameIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageRotatedIn,
	FIntPoint ItemDimensionsIn, USGInventoryComponent* InventoryComponentIn, EEquipmentType TypeIn)
{
}

void UInventoryItem::ReturnBack()
{
	Rotate();
	LastInventoryComponent->AddItem(this, LastIndex);
}

FIntPoint UInventoryItem::GetItemDimensions() const
{
	if(bIsRotated)
	{
		FIntPoint RotateDimensions(ItemDimensions.Y, ItemDimensions.X);
		return RotateDimensions;
	}

	return ItemDimensions;
}

void UInventoryItem::Rotate()
{
	bIsRotated = !bIsRotated;
}
