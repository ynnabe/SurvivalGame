// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SGBaseCharacter.generated.h"

class USGCharacterAttributes;
class USGCharacterMovementComponent;
UCLASS()
class SURVIVALGAME_API ASGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGBaseCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Move(const FInputActionValue& Value) {};
	virtual void Look(const FInputActionValue& Value) {};
	virtual void Jump() override;

	FORCEINLINE USGCharacterAttributes* GetCharacterAttributes() const { return SGCharacterAttributes; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USGCharacterMovementComponent* SGCharacterMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	USGCharacterAttributes* SGCharacterAttributes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action costs")
	float JumpCost = 15.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Restore parameters")
	float RestorStaminaCoolDown = 2.0f;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	FTimerHandle CDStaminaTimer;

};
