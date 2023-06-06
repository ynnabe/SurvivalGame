// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

class ASGPlayerCharacter;

enum EquipmentSlot
{
	Torso,
	Backpack
};

class AEquipment;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API UEquipmentComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEquipmentComponent();

	bool EquipGear(EquipmentSlot Slot, UEquipmentItem* Equipment);

	bool SetItemInSlot(UEquipmentItem* EquipmentItem);

	UFUNCTION(BlueprintPure)
	FORCEINLINE UEquipmentItem* GetTorsoSlot() const { return TorsoSlot; }
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE UEquipmentItem* GetBackpackSlot() const { return BackpackSlot; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment slots")
	UEquipmentItem* TorsoSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment slots")
	UEquipmentItem* BackpackSlot;

private:

	UPROPERTY()
	ASGPlayerCharacter* CachedPlayer;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
