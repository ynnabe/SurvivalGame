// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "SGInventoryComponent.generated.h"

class UEquipmentItem;
DECLARE_DELEGATE(FOnInventoryChangedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API USGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGInventoryComponent();

	void Initialize();

	FOnInventoryChangedSignature OnInventoryChanged;

	void SetCapacity(int32 NewColumns, int32 NewRows);
	void SetItems(TArray<UInventoryItem*> NewItems);

	bool TryAddItem(UInventoryItem* ItemToAdd);
	bool IsRoomAvailable(UInventoryItem* Item, int32 TopLeftIndex);
	UInventoryItem* GetItemAtIndex(int32 Index);
	FInventoryTile IndexToTile(int32 Index) const;
	int32 TileToIndex(FInventoryTile* Tile);

	void AddItem(UInventoryItem* ItemToAdd, int32 TopLeftIndex);
	void RemoveItem(UInventoryItem* ItemToRemove, bool bNeedToDrop);
	void DropItem(UInventoryItem* ItemToDrop);

	TMap<UInventoryItem*, FInventoryTile> GetItemsAsMap() const;
	FORCEINLINE int32 GetColumns() const { return Columns; }
	FORCEINLINE int32 GetRows() const { return Rows; }
	FORCEINLINE TArray<UInventoryItem*> GetItems() const { return Items; }

	void SetPlayerOwner(ASGBaseCharacter* Player);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | Parameters", DisplayName="Кол-во слотов в ширину")
	int32 Columns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | Parameters", DisplayName="Кол-во слотов в длину")
	int32 Rows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TArray<UInventoryItem*> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TSubclassOf<AItem> ItemBaseClass;

private:

	TWeakObjectPtr<UEquipmentItem> EquipmentOwner;
	TWeakObjectPtr<ASGBaseCharacter> PlayerOwner;

	bool bIsDirty = false;

		
};
