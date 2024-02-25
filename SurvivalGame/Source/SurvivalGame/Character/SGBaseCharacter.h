// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SurvivalGame/UI/SGPlayerWidget.h"
#include "SGBaseCharacter.generated.h"

class USGCharacterAnimInstance;
class UInventoryItem;
class ASGPlayerController;
class UEquipmentComponent;
class USGCharacterAttributes;
class USGCharacterMovementComponent;
UCLASS()
class SURVIVALGAME_API ASGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void Move(const FInputActionValue& Value) {};
	virtual void Look(const FInputActionValue& Value) {};
	virtual void Jump() override;
	virtual void Landed(const FHitResult& Hit) override;

	virtual void Interact();
	virtual void UseInventory() {};

	virtual void StartSprint();
	virtual void StopSprint();

	virtual bool TryAddItem(UInventoryItem* Item) { return true; };

	UFUNCTION(Server, Unreliable)
	void Server_ToggleJump(bool NewState);

	UFUNCTION(Server, Reliable)
	void Server_StartAttributesSprint();

	UFUNCTION(Server, Reliable)
	void Server_StopAttributesSprint();

	UFUNCTION(BlueprintPure)
	FORCEINLINE USGCharacterAttributes* GetCharacterAttributes() const { return SGCharacterAttributes; }

	UFUNCTION(BlueprintPure)
	FORCEINLINE UEquipmentComponent* GetEquipmentComponent() const { return SGEquipmentComponent; }

	FORCEINLINE ASGPlayerController* GetPlayerController() const { return PlayerController; }

	void SpawnDropedItem(UInventoryItem* ItemToSpawn);
	
	UPROPERTY(Replicated)
	bool bIsJumping = false;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USGCharacterMovementComponent* SGCharacterMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USGCharacterAttributes* SGCharacterAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UEquipmentComponent* SGEquipmentComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action costs")
	float JumpCost = 15.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action costs")
	float RestoreStaminaCoolDown = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<USGPlayerWidget> PlayerHUDWidgetClass;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UPROPERTY()
	USGPlayerWidget* PlayerHUDWidget = nullptr;

	UPROPERTY()
	USGCharacterAnimInstance* PlayerAnimInstance;

	UPROPERTY()
	ASGPlayerController* PlayerController;

	FTimerHandle CDStaminaTimer;

};
