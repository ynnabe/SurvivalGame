// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentComponent.generated.h"

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

	bool EquipGear(EquipmentSlot Slot, AEquipment* Equipment);

	bool SetItemInSlot(AEquipment* EquipmentItem);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment slots")
	AEquipment* TorsoSlot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Equipment slots")
	AEquipment* BackpackSlot;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
