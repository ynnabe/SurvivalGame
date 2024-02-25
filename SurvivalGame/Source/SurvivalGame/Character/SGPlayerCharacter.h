// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGBaseCharacter.h"
#include "SGPlayerCharacter.generated.h"

class UInventoryWidget;
DECLARE_DELEGATE_TwoParams(FInteractableDetectedSignature, bool, FText);
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ASGPlayerCharacter : public ASGBaseCharacter
{
	GENERATED_BODY()

public:

	ASGPlayerCharacter(const FObjectInitializer& ObjectInitializer);
	void CreateInventoryWidget();

	virtual void BeginPlay() override;

	FInteractableDetectedSignature InteractableDetected;

	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

	virtual void StartSprint() override;
	virtual void StopSprint() override;

	virtual void Interact() override;

	virtual void UseInventory() override;

	virtual bool TryAddItem(UInventoryItem* Item) override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Server, Reliable)
	void Server_DestroyInteractItem(AActor* ActorToDestroy);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_DestroyInteractItem(AActor* ActorToDestroy);

	UFUNCTION(Client, Unreliable)
	void Client_InteractLineTrace();

	FORCEINLINE UInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class USkeletalMeshComponent* FPSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactable parameters")
	float InteractTraceLength = 300.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="InventoryWidgetClass")
	TSubclassOf<UInventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	USoundBase* PickUpSound;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnStartSprint();

	UFUNCTION(BlueprintNativeEvent)
	void OnStopSprint();

private:

	UPROPERTY()
	UInventoryWidget* InventoryWidget;

	UPROPERTY()
	USGCharacterAnimInstance* FPPlayerAnimInstance;

	UPROPERTY()
	bool bIsInventoryVisible = false;

	UPROPERTY()
	AActor* InteractableLineObject;
};
