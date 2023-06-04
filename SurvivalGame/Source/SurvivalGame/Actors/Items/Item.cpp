// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"

#include "SurvivalGame/Actors/Equipment/Equipment.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"
#include "SurvivalGame/Components/Character/EquipmentComponent.h"
#include "SurvivalGame/Inventory/InventoryItem.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
}

void AItem::SetDetect(bool NewValue)
{
	bIsDetected = NewValue;
}

void AItem::DetectedByTraceInteract_Implementation()
{
	if(!IsDetected())
	{
		MeshComponent->SetOverlayMaterial(OverlayMaterial);
		bIsDetected = true;
	}
	else
	{
		UMaterialInterface* EmptyMaterial = nullptr;
		MeshComponent->SetOverlayMaterial(EmptyMaterial);
		bIsDetected = false;
	}
}

void AItem::InteractPure(ASGBaseCharacter* Character)
{
	if(Character->GetEquipmentComponent()->GetTorsoSlot()->GetInventoryComponent()->TryAddItem(Item))
	{
		Destroy();
	}
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	Item = SetupItem();
}

UInventoryItem* AItem::SetupItem()
{
	UInventoryItem* ItemNew = NewObject<UInventoryItem>();
	
	ItemNew->Name = Name;
	ItemNew->Image = Image;
	ItemNew->ImageRotated = ImageRotated;
	ItemNew->ItemDimensions = ItemDimensions;
	ItemNew->MeshComponent = MeshComponent;
	
	return ItemNew;
}

