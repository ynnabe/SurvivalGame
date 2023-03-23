// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBaseCharacter.h"
#include "Net/UnrealNetwork.h"
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

void ASGBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ASGBaseCharacter, bIsJumping);
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

			Server_ToggleJump(true);
		}
	}
}

void ASGBaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	Server_ToggleJump(false);
}

void ASGBaseCharacter::StartSprint()
{
	SGCharacterMovementComponent->SetIsSprinting(true);
	if(IsLocallyControlled())
	{
		Server_StartAttributesSprint();
	}
}

void ASGBaseCharacter::StopSprint()
{
	SGCharacterMovementComponent->SetIsSprinting(false);
	if(IsLocallyControlled())
	{
		Server_StopAttributesSprint();
	}
}

void ASGBaseCharacter::Server_ToggleJump_Implementation(bool NewState)
{
	bIsJumping = NewState;
}

void ASGBaseCharacter::Server_StartAttributesSprint_Implementation()
{
	SGCharacterAttributes->bIsSprinting = true;
}

void ASGBaseCharacter::Server_StopAttributesSprint_Implementation()
{
	SGCharacterAttributes->bIsSprinting = false;
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

