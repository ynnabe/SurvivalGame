// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "SurvivalGame/Actors/Equipment/Equipment.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"
#include "SurvivalGame/Components/Character/EquipmentComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

bool AItem::IsEmpty() const
{
	if(IsValid(Image))
	{
		return true;
	}

	return false;
}

void AItem::DetectedByTraceInteract_Implementation()
{
}

void AItem::InteractPure(ASGBaseCharacter* Character)
{
	Character->GetEquipmentComponent()->GetTorsoSlot()->GetInventoryComponent()->TryAddItem(this);
	Destroy();
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

