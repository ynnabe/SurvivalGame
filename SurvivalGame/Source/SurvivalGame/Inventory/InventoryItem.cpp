// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"

void UInventoryItem::Initialize(FText NameIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageRotatedIn,
                                FIntPoint ItemDimensionsIn, TSubclassOf<AItem> ItemActorClass_In)
{
	Name = NameIn;
	Image = ImageIn;
	ImageRotated = ImageRotatedIn;
	ItemDimensions = ItemDimensionsIn;
	SetItemActorClass(ItemActorClass_In);
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

void UInventoryItem::SetItemActorClass(TSubclassOf<AItem> ItemActorClass_In)
{
	ItemActorClass = ItemActorClass_In;
}
