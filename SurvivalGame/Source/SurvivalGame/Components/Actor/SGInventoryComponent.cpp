// Fill out your copyright notice in the Description page of Project Settings.


#include "SGInventoryComponent.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "SurvivalGame/Inventory/InventoryItem.h"
#include "Kismet/KismetArrayLibrary.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/Inventory/Equipment/EquipmentItem.h"

USGInventoryComponent::USGInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	
}

void USGInventoryComponent::Initialize()
{
	for(int Index = 0; Index <= Columns * Rows; Index++)
	{
		Items.Add(nullptr);
	}
}

void USGInventoryComponent::SetCapacity(int32 NewColumns, int32 NewRows)
{
	Columns = NewColumns;
	Rows = NewRows;
}

void USGInventoryComponent::SetItems(TArray<UInventoryItem*> NewItems)
{
	Items = NewItems;
}

bool USGInventoryComponent::TryAddItem(UInventoryItem* ItemToAdd)
{
	if(!IsValid(ItemToAdd))
	{
		return false;
	}

	for(int Index = 0; Index < Items.Num(); Index++)
	{
		if(IsRoomAvailable(ItemToAdd, Index))
		{
			AddItem(ItemToAdd, Index);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Item added")));
			return true;
		}
	}

	ItemToAdd->Rotate();

	for(int Index = 0; Index < Items.Num(); Index++)
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

bool USGInventoryComponent::IsRoomAvailable(UInventoryItem* Item, int32 TopLeftIndex)
{
	FInventoryTile Tile = IndexToTile(TopLeftIndex);
	FIntPoint ItemDimensions = Item->GetItemDimensions();

	for(int X = Tile.X; X < Tile.X + (ItemDimensions.X); X++)
	{
		for(int Y = Tile.Y; Y < Tile.Y + (ItemDimensions.Y); Y++)
		{
			FInventoryTile OutTile(X, Y);
			if(OutTile.X >= 0 && OutTile.Y >= 0 && OutTile.X < Columns && OutTile.Y < Rows)
			{
				if(GetItemAtIndex(TileToIndex(&OutTile)))
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
	}
	
	return true;
}

UInventoryItem* USGInventoryComponent::GetItemAtIndex(int32 Index)
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

int32 USGInventoryComponent::TileToIndex(FInventoryTile* Tile)
{
	if(Tile)
	{
		return Tile->X + Tile->Y * Columns;
	}

	return 0;
}

void USGInventoryComponent::AddItem(UInventoryItem* ItemToAdd, int32 TopLeftIndex)
{
	FInventoryTile Tile = IndexToTile(TopLeftIndex);
	FIntPoint ItemDimensions = ItemToAdd->GetItemDimensions();

	for(int X = Tile.X; X < Tile.X + (ItemDimensions.X); X++)
	{
		for(int Y = Tile.Y; Y < Tile.Y + (ItemDimensions.Y); Y++)
		{
			FInventoryTile OutTile(X, Y);
			int32 IndexToInsert = TileToIndex(&OutTile);
			Items[IndexToInsert] = ItemToAdd;
			Items[IndexToInsert]->SetLastInventoryComponent(this);
			Items[IndexToInsert]->SetLastIndex(TopLeftIndex);
		}
	}

	if(OnInventoryChanged.IsBound())
	{
		OnInventoryChanged.Execute();
	}

	bIsDirty = true;
}

void USGInventoryComponent::RemoveItem(UInventoryItem* ItemToRemove, bool bNeedToDrop)
{
	if(IsValid(ItemToRemove))
	{
		if(bNeedToDrop)
		{
			DropItem(ItemToRemove);
		}
		for (auto &Item : Items)
		{
			if(IsValid(Item))
			{
				if(Item == ItemToRemove)
				{
					Item = nullptr;
				}
			}
		}
	}
}

void USGInventoryComponent::DropItem(UInventoryItem* ItemToDrop)
{
	PlayerOwner->SpawnDropedItem(ItemToDrop);
}

TMap<UInventoryItem*, FInventoryTile> USGInventoryComponent::GetItemsAsMap() const
{
	TMap<UInventoryItem*, FInventoryTile> AllItems;

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

void USGInventoryComponent::SetPlayerOwner(ASGBaseCharacter* Player)
{
	PlayerOwner = Player;
}

void USGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
}

