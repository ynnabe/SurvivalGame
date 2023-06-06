// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment.h"

#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/Character/SGPlayerCharacter.h"
#include "SurvivalGame/Components/Actor/SGInventoryComponent.h"
#include "SurvivalGame/Components/Character/EquipmentComponent.h"
#include "SurvivalGame/Inventory/Equipment/EquipmentItem.h"
#include "SurvivalGame/UI/Inventory/InventoryWidget.h"

AEquipment::AEquipment()
{
	InventoryComponent = CreateDefaultSubobject<USGInventoryComponent>(TEXT("InventoryComponent"));
}

void AEquipment::InitializeItem()
{
	UEquipmentItem* NewEquipmentItem = NewObject<UEquipmentItem>();

	NewEquipmentItem->Initialize(Name, Image, ImageRotated, ItemDimensions, InventoryComponent, Type);
	
	EquipmentItem = NewEquipmentItem;
}

FText AEquipment::GetItemName() const
{
	return Super::GetItemName();
}

void AEquipment::DetectedByTraceInteract_Implementation()
{
	Super::DetectedByTraceInteract_Implementation();
}

void AEquipment::InteractPure(ASGBaseCharacter* Character)
{
	UEquipmentComponent* CharacterEquipmentComponent = Character->GetEquipmentComponent();
	InitializeItem();
	if(CharacterEquipmentComponent->SetItemInSlot(EquipmentItem))
	{
		Destroy();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Can't pick up item")));
	}
}

void AEquipment::BeginPlay()
{
	Super::BeginPlay();
}
