// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBaseCharacter.h"

#include "SurvivalGame/Components/Character/SGCharacterAttributes.h"
#include "SurvivalGame/Components/Character/SGCharacterMovementComponent.h"


ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SGCharacterMovementComponent = Cast<USGCharacterMovementComponent>(GetCharacterMovement());
	SGCharacterAttributes = CreateDefaultSubobject<USGCharacterAttributes>(TEXT("CharacterAttributes"));
}


void ASGBaseCharacter::Jump()
{
	if(GetCharacterAttributes()->GetStamina() > JumpCost)
	{
		Super::Jump();

		GetCharacterAttributes()->SetStamina(GetCharacterAttributes()->GetStamina() - JumpCost);
		GetCharacterAttributes()->SetCDStamina(true);
		if(GetWorld()->GetTimerManager().IsTimerActive(CDStaminaTimer))
		{
			GetWorld()->GetTimerManager().ClearTimer(CDStaminaTimer);
		}
		GetWorld()->GetTimerManager().SetTimer(CDStaminaTimer, [=]()
		{
			GetCharacterAttributes()->SetCDStamina(false);
		}, RestorStaminaCoolDown, false);
	}
}

void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

