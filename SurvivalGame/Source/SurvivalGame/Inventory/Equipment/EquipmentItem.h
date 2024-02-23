// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "SurvivalGame/Inventory/InventoryItem.h"
#include "EquipmentItem.generated.h"

class USGInventoryComponent;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UEquipmentItem : public UInventoryItem
{
	GENERATED_BODY()

public:

	UEquipmentItem();

	virtual void Initialize(FText NameIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageRotatedIn, FIntPoint ItemDimensionsIn, USGInventoryComponent* InventoryComponentIn, EEquipmentType TypeIn) override;
	
	FORCEINLINE USGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE EEquipmentType GetType() const { return Type; }
	FORCEINLINE ASGBaseCharacter* GetPlayerOwner() const { return CachedOwner.Get(); }

	void SetPlayerOwner(ASGBaseCharacter* Player);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment parameters")
	EEquipmentType Type;

private:

	TWeakObjectPtr<ASGBaseCharacter> CachedOwner;
	
};
