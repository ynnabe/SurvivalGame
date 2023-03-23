// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "SurvivalGame/Components/Character/SGCharacterMovementComponent.h"

ASGPlayerCharacter::ASGPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh());
	CameraComponent->bUsePawnControlRotation = true;
}

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

void ASGPlayerCharacter::StartSprint()
{
	Super::StartSprint();
	OnStartSprint();
}

void ASGPlayerCharacter::StopSprint()
{
	Super::StopSprint();
	OnStopSprint();
}

void ASGPlayerCharacter::OnStopSprint_Implementation()
{
}

void ASGPlayerCharacter::OnStartSprint_Implementation()
{
}
