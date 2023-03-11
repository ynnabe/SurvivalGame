// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerCharacter.h"

void ASGPlayerCharacter::Move(const FInputActionValue& Value)
{
	Super::Move(Value);
	
	AddMovementInput(GetActorForwardVector(), Value[1]);
	AddMovementInput(GetActorRightVector(), Value[0]);
}

void ASGPlayerCharacter::Look(const FInputActionValue& Value)
{
	Super::Look(Value);

	AddControllerPitchInput(Value[1] * -1);
	AddControllerYawInput(Value[0]);
}
