// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AEquipable.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "Equipment.generated.h"

class UEquipmentItem;
class USGInventoryComponent;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API AEquipment : public AAEquipable
{
	GENERATED_BODY()

public:

	AEquipment();

	virtual void InitializeItem() override;

	virtual FText GetItemName() const override;

	FORCEINLINE EEquipmentType GetType() const { return Type; }
	FORCEINLINE USGInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	virtual void DetectedByTraceInteract_Implementation() override;


#pragma region InteractableInterface
	virtual void InteractPure(ASGBaseCharacter* Character) override;
#pragma endregion
	
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory Component")
	USGInventoryComponent* InventoryComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Equipment parameters")
	EEquipmentType Type;

private:

	UPROPERTY()
	UEquipmentItem* EquipmentItem;
};
