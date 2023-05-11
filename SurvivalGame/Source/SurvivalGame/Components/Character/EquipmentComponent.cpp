// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentComponent.h"

#include "SurvivalGame/Actors/Equipment/Equipment.h"
#include "SurvivalGame/Character/SGPlayerCharacter.h"
#include "SurvivalGame/UI/Inventory/InventoryWidget.h"

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

bool UEquipmentComponent::SetItemInSlot(AEquipment* EquipmentItem)
{
	switch(EquipmentItem->GetType())
	{
		case EEquipmentType::None:
			{
				return false;
			}
		case EEquipmentType::Torso:
			{
				if(!IsValid(TorsoSlot))
				{
					TorsoSlot = EquipmentItem;
					CachedPlayer->GetInventoryWidget()->SetTorsoEquipmentWidget(TorsoSlot->GetInventoryComponent());
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s equiped in Torso slot"), *EquipmentItem->GetItemName().ToString()));
					return true;
				}
				return false;
			}
		case EEquipmentType::Backpack:
			{
				if(!IsValid(BackpackSlot))
				{
					BackpackSlot = EquipmentItem;
					CachedPlayer->GetInventoryWidget()->SetBackpackEquipmentWidget(BackpackSlot->GetInventoryComponent());
					GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("%s equiped in Backpack slot"), *EquipmentItem->GetItemName().ToString()));
					return true;
				}
				return false;
			}
	}
	
	return false;
}

void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CachedPlayer = Cast<ASGPlayerCharacter>(GetOwner());
}

void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

