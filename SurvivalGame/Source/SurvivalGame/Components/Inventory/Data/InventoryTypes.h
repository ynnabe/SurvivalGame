// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SurvivalGame/Actors/Items/Item.h"
#include "Math/Vector2D.h"
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

USTRUCT(BlueprintType)
struct FGridLine
{
	GENERATED_BODY()

	FGridLine()
	{
		StartPoint = FVector2d(0.0f, 0.0f);
		EndPoint = FVector2d(0.0f, 0.0f);
	}

	FGridLine(FVector2d Start, FVector2d End)
	{
		StartPoint = Start;
		EndPoint = End;
	}
	
	FVector2d StartPoint;
	FVector2d EndPoint;
};

USTRUCT(BlueprintType)
struct FInventoryTile
{
	GENERATED_BODY()

	FInventoryTile()
	{
		X = -0;
		Y = -0;
	}

	FInventoryTile(int32 X_in, int32 Y_in)
	{
		this->X = X_in;
		this->Y = Y_in;
	}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Y;
};

UENUM()
enum class EEquipmentType : uint8
{
	None,
	Torso,
	Backpack
};

