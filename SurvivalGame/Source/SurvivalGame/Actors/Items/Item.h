// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivalGame/Interfaces/SGInteractableInterface.h"
#include "Item.generated.h"

class UInventoryItem;
UCLASS()
class SURVIVALGAME_API AItem : public AActor, public ISGInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AItem();

	/*AItem(const AItem* Other)
	{
		this->Name = Other->Name;
		this->NameCheck = Other->NameCheck;
		this->Image = Other->Image;
		this->ImageRotated = Other->ImageRotated;
		this->MeshComponent = Other->MeshComponent;
		this->bIsRotated = Other->bIsRotated;
		this->ItemDimensions = Other->ItemDimensions;
	}*/

	UInventoryItem* GetItem() const { return Item; }

	FORCEINLINE virtual FText GetItemName() const { return Name; }
	FORCEINLINE bool IsDetected() const { return bIsDetected; }

	void SetDetect(bool NewValue);

	/*FORCEINLINE FIntPoint GetItemDimensions() const { return ItemDimensions; }

	UMaterialInterface* GetItemIcon() const { return bIsRotated ? ImageRotated : Image; }*/

#pragma region InteractableInterface
	void DetectedByTraceInteract_Implementation() override;
	
	virtual void InteractPure(ASGBaseCharacter* Character) override;
#pragma endregion InteractableInterface
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item")
	UInventoryItem* Item;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FText Name = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FName NameCheck = NAME_None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UMaterialInterface* Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UMaterialInterface* ImageRotated;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FIntPoint ItemDimensions = FIntPoint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UMaterialInterface* OverlayMaterial;

private:

	UInventoryItem* SetupItem();

	bool bIsDetected = false;

	/*bool bIsRotated = false;*/

};
