// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerCharacter.h"

#include "SurvivalGame/Components/Character/SGCharacterMovementComponent.h"

void ASGPlayerCharacter::Move(const FInputActionValue& Value)
{
	Super::Move(Value);

	if(!SGCharacterMovementComponent->GetIsSprinting())
	{
		AddMovementInput(GetActorForwardVector(), Value[1]);
		AddMovementInput(GetActorRightVector(), Value[0]);
	}
	else
	{
		if(Value[1] > 0.0f)
		{
			AddMovementInput(GetActorForwardVector(), Value[1]);
		}
	}
}

void ASGPlayerCharacter::Look(const FInputActionValue& Value)
{
	Super::Look(Value);

	AddControllerPitchInput(Value[1] * -1);
	AddControllerYawInput(Value[0]);
}
