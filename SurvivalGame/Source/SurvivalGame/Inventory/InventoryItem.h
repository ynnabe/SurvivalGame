// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UInventoryItem : public UObject
{
	GENERATED_BODY()
	
public:

	FORCEINLINE FIntPoint GetItemDimensions() const;

	UMaterialInterface* GetItemIcon() const { return bIsRotated ? ImageRotated : Image; }

	void Rotate();

	bool IsRotated() const { return bIsRotated; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FText Name = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UMaterialInterface* Image = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UMaterialInterface* ImageRotated = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UStaticMeshComponent* MeshComponent = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FIntPoint ItemDimensions = FIntPoint();

private:

	bool bIsRotated = false;
	
};
