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

	GetMesh()->SetOwnerNoSee(true);
}


void ASGBaseCharacter::Jump()
{
	if(!SGCharacterMovementComponent->IsFalling())
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
			}, RestoreStaminaCoolDown, false);
		}
	}
}


void ASGBaseCharacter::Client_Jump_Implementation()
{
	GetCharacterAttributes()->SetStamina(GetCharacterAttributes()->GetStamina() - JumpCost);
	GetCharacterAttributes()->SetCDStamina(true);
	if(GetWorld()->GetTimerManager().IsTimerActive(CDStaminaTimer))
	{
		GetWorld()->GetTimerManager().ClearTimer(CDStaminaTimer);
	}
	GetWorld()->GetTimerManager().SetTimer(CDStaminaTimer, [=]()
	{
		GetCharacterAttributes()->SetCDStamina(false);
	}, RestoreStaminaCoolDown, false);
}

void ASGBaseCharacter::StartSprint()
{
	if(IsLocallyControlled())
	{
		Server_StartSprint();
	}
}

void ASGBaseCharacter::StopSprint()
{
	if(IsLocallyControlled())
	{
		Server_StopSprint();
	}
}

void ASGBaseCharacter::Server_StartSprint_Implementation()
{
	SGCharacterAttributes->bIsSprinting = true;
	SGCharacterMovementComponent->SetIsSprinting(true);
}

void ASGBaseCharacter::Server_StopSprint_Implementation()
{
	SGCharacterAttributes->bIsSprinting = false;
	SGCharacterMovementComponent->SetIsSprinting(false);
}

void ASGBaseCharacter::Client_StartSprint_Implementation()
{
	SGCharacterMovementComponent->SetIsSprinting(true);
}

void ASGBaseCharacter::Client_StopSprint_Implementation()
{
	SGCharacterMovementComponent->SetIsSprinting(false);
}

void ASGBaseCharacter::Server_Jump_Implementation()
{
	if(GetLocalRole() == ROLE_Authority)
	{
		Client_Jump();
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

