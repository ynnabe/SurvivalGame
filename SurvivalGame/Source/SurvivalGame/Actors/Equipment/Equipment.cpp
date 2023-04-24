// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"
#include "SurvivalGame/Components/Character/EquipmentComponent.h"

AEquipment::AEquipment()
{
	InventoryComponent = CreateDefaultSubobject<USGInventoryComponent>(TEXT("InventoryComponent"));
}

FName AEquipment::GetItemName() const
{
	return Super::GetItemName();
}

void AEquipment::InteractPure(ASGBaseCharacter* Character)
{
	UEquipmentComponent* CharacterEquipmentComponent = Character->GetEquipmentComponent();
	if(CharacterEquipmentComponent->SetItemInSlot(this))
	{
		Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Can't pick up item")));
	}
}
