// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItem.h"

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
