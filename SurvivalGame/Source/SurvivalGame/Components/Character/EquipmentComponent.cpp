// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

UEquipmentComponent::UEquipmentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

bool UEquipmentComponent::EquipGear(EquipmentSlot Slot, AEquipment* Equipment)
{
	switch (Slot)
	{
		case Torso:
			{
				if(!TorsoSlot)
				{
					TorsoSlot = Equipment;
					return true;
				}
			}
		case Backpack:
			{
				if(!BackpackSlot)
				{
					BackpackSlot = Equipment;
					return true;
				}
			}
		default:
		{
			return false;
		}
	}
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}

void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

