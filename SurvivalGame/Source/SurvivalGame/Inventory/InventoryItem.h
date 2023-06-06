// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "UObject/NoExportTypes.h"
#include "InventoryItem.generated.h"

class USGInventoryComponent;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UInventoryItem : public UObject
{
	GENERATED_BODY()
	
public:

	virtual void Initialize(FText NameIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageRotatedIn, FIntPoint ItemDimensionsIn);
	virtual void Initialize(FText NameIn, UMaterialInterface* ImageIn, UMaterialInterface* ImageRotatedIn, FIntPoint ItemDimensionsIn, USGInventoryComponent* InventoryComponentIn, EEquipmentType TypeIn);
	
	void SetLastInventoryComponent(USGInventoryComponent* InventoryComponent) { LastInventoryComponent = InventoryComponent; }
	void SetLastIndex(int32 Index) { LastIndex = Index; }

	void ReturnBack();

	FORCEINLINE FIntPoint GetItemDimensions() const;

	UMaterialInterface* GetItemIcon() const { return bIsRotated ? ImageRotated : Image; }

	void Rotate();

	bool IsRotated() const { return bIsRotated; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UMaterialInterface* Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UMaterialInterface* ImageRotated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FIntPoint ItemDimensions = FIntPoint();

private:

	UPROPERTY()
	USGInventoryComponent* LastInventoryComponent;
	int32 LastIndex;

	bool bIsRotated = false;
	
};
