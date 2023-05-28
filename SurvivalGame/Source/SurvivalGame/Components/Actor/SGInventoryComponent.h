// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "SGInventoryComponent.generated.h"

DECLARE_DELEGATE(FOnInventoryChangedSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API USGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGInventoryComponent();

	FOnInventoryChangedSignature OnInventoryChanged;

	bool TryAddItem(AItem* ItemToAdd);
	bool IsRoomAvailable(AItem* Item, int32 TopLeftIndex);
	AItem* GetItemAtIndex(int32 Index);
	FInventoryTile IndexToTile(int32 Index) const;
	int32 TileToIndex(FInventoryTile Tile);

	void AddItem(AItem* ItemToAdd, int32 TopLeftIndex);
	void RemoveItem(AItem* ItemToRemove);

	TMap<AItem, FInventoryTile> GetItemsAsMap() const;
	FORCEINLINE int32 GetColumns() const { return Columns; }
	FORCEINLINE int32 GetRows() const { return Rows; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | Parameters", DisplayName="Кол-во слотов в длину")
	int32 Columns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | Parameters", DisplayName="Кол-во слотов в ширину")
	int32 Rows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TArray<AItem*> Items;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory")
	TSubclassOf<AItem> ItemBaseClass;

private:	

	bool bIsDirty = false;

		
};
