// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "SGInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API USGInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGInventoryComponent();

	FORCEINLINE TMap<int32, FInventoryRow>& GetItems() { return InventorySlots; }

	FORCEINLINE int32 GetColumns() const { return Columns; }
	FORCEINLINE int32 GetRows() const { return Rows; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 HeightSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 WidthSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | Parameters", DisplayName="Кол-во слотов в длину")
	int32 Columns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Inventory | Parameters", DisplayName="Кол-во слотов в ширину")
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory | Slots")
	TMap<int32, FInventoryRow> InventorySlots;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
