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
	
	virtual void InitializeItem();

	UInventoryItem* GetItem() const { return Item; }

	FORCEINLINE virtual FText GetItemName() const { return Name; }
	FORCEINLINE bool IsDetected() const { return bIsDetected; }

	void SetDetect(bool NewValue);

	UFUNCTION(Server, Reliable)
	void Server_DestroyItem();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DestroyItem();

#pragma region InteractableInterface
	void DetectedByTraceInteract_Implementation() override;
	
	virtual void InteractPure(ASGBaseCharacter* Character) override;
#pragma endregion InteractableInterface
	
protected:
	virtual void BeginPlay() override;
	
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
	
	UPROPERTY()
	UInventoryItem* Item;

	bool bIsDetected = false;

};
