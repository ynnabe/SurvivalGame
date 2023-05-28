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

AItem::AItem(FText NameIn, FName NameCheckIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageVerticalIn,
	FIntPoint Dimensions)
{
	Name = NameIn;
	NameCheck = NameCheckIn;
	Image = ImageIn;
	ImageRotated = ImageVerticalIn;
	ItemDimensions = Dimensions;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

bool AItem::IsEmpty() const
{
	if(NameCheck == NAME_None)
	{
		return true;
	}

	return false;
}

void AItem::SetNameCheck(FName NewName)
{
	NameCheck = NewName;
}

void AItem::DetectedByTraceInteract_Implementation()
{
}

void AItem::InteractPure(ASGBaseCharacter* Character)
{
	if(Character->GetEquipmentComponent()->GetTorsoSlot()->GetInventoryComponent()->TryAddItem(this))
	{
		Destroy();
	}
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

