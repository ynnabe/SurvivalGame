// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SurvivalGame/Actors/Items/Item.h"
#include "InventoryTypes.generated.h"

USTRUCT(BlueprintType)
struct FInventorySlot
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	AItem* Item;

	AItem* IsItemInSlot() const
	{
		return Item;
	}

	FInventorySlot()
	{
		this->Item = nullptr;
	}

	FInventorySlot(AItem* Item)
	{
		this->Item = Item;
	}
};

USTRUCT(BlueprintType)
struct FInventoryRow
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FInventorySlot> Row;
};

UENUM()
enum class EEquipmentType : uint8
{
	None,
	Torso,
	Backpack
};

