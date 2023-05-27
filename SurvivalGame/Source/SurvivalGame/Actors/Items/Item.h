// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivalGame/Interfaces/SGInteractableInterface.h"
#include "Item.generated.h"

UCLASS()
class SURVIVALGAME_API AItem : public AActor, public ISGInteractableInterface
{
	GENERATED_BODY()
	
public:	
	AItem();

	bool IsEmpty() const;

	FORCEINLINE virtual FText GetItemName() const { return Name; }

	FORCEINLINE FIntPoint GetItemDimensions() const { return ItemDimensions; }

#pragma region InteractableInterface
	void DetectedByTraceInteract_Implementation() override;
	
	virtual void InteractPure(ASGBaseCharacter* Character) override;
#pragma endregion InteractableInterface
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FText Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UTexture2D* Image;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Item parameters")
	FIntPoint ItemDimensions;

public:	
	virtual void Tick(float DeltaTime) override;

};
