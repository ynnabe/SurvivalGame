// Fill out your copyright notice in the Description page of Project Settings.


#include "SGInventoryComponent.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "Kismet/KismetArrayLibrary.h"

USGInventoryComponent::USGInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

bool USGInventoryComponent::TryAddItem(AItem* ItemToAdd)
{
	if(!IsValid(ItemToAdd))
	{
		return false;
	}

	for(int Index = 0; Index <= Items.Num(); Index++)
	{
		if(IsRoomAvailable(ItemToAdd, Index))
		{
			AddItem(ItemToAdd, Index);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Item added")));
			return true;
		}
	}
	
	return false;
}

bool USGInventoryComponent::IsRoomAvailable(AItem* Item, int32 TopLeftIndex)
{
	FInventoryTile Tile = IndexToTile(TopLeftIndex);
	FIntPoint ItemDimensions = Item->GetItemDimensions();

	for(int X = Tile.X; X <= Tile.X + (ItemDimensions.X - 1); X++)
	{
		for(int Y = Tile.Y; Y <= Tile.Y + (ItemDimensions.Y - 1); Y++)
		{
			FInventoryTile OutTile(X, Y);
			if(OutTile.X > 0 && OutTile.Y > 0)
			{
				if(AItem* ItemAtIndex = GetItemAtIndex(TileToIndex(OutTile)))
				{
					return false;
				}
			}
		}
	}
	
	return true;
}

AItem* USGInventoryComponent::GetItemAtIndex(int32 Index)
{
	if(Items.IsValidIndex(Index))
	{
		return Items[Index];
	}

	return nullptr;
}

FInventoryTile USGInventoryComponent::IndexToTile(int32 Index) const
{
	return FInventoryTile(Index % Columns, Index / Columns);
}

int32 USGInventoryComponent::TileToIndex(FInventoryTile Tile)
{
	return Tile.X + Tile.Y * Columns;
}

void USGInventoryComponent::AddItem(AItem* ItemToAdd, int32 TopLeftIndex)
{
	FInventoryTile Tile = IndexToTile(TopLeftIndex);
	FIntPoint ItemDimensions = ItemToAdd->GetItemDimensions();

	for(int X = Tile.X; X <= Tile.X + (ItemDimensions.X - 1); X++)
	{
		for(int Y = Tile.Y; Y <= Tile.Y + (ItemDimensions.Y - 1); Y++)
		{
			FInventoryTile OutTile(X, Y);
			int32 IndexToInsert = TileToIndex(OutTile);
			Items[IndexToInsert] = ItemToAdd;
		}
	}

	if(OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Execute();
	}

	bIsDirty = true;
}

void USGInventoryComponent::RemoveItem(AItem* ItemToRemove)
{
	
}

TMap<AItem, FInventoryTile> USGInventoryComponent::GetItemsAsMap() const
{
	TMap<AItem, FInventoryTile> AllItems;

	for(int Index = 0; Index < Items.Num(); Index++)
	{
		if(IsValid(Items[Index]))
		{
			if(!AllItems.Contains(Items[Index]))
			{
				FInventoryTile Tile = IndexToTile(Index);

				AllItems.Add(Items[Index], Tile);
			}
		}
	}
	
	return AllItems;
}

void USGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for(int Index = 0; Index <= Columns * Rows; Index++)
	{
		Items.Add(nullptr);
	}
}

