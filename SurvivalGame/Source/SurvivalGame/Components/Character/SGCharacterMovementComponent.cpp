// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCharacterMovementComponent.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"

USGCharacterMovementComponent::USGCharacterMovementComponent()
{
	SetIsReplicatedByDefault(true);
}

FNetworkPredictionData_Client* USGCharacterMovementComponent::GetPredictionData_Client() const
{
	if(ClientPredictionData == nullptr)
	{
		USGCharacterMovementComponent* MutableThis = const_cast<USGCharacterMovementComponent*>(this);
		MutableThis->ClientPredictionData = new FNetworkPredictionData_Client_SGCharacter(*this);
	}
	return ClientPredictionData;
}

void USGCharacterMovementComponent::UpdateFromCompressedFlags(uint8 Flags)
{
	Super::UpdateFromCompressedFlags(Flags);

	/*
	FLAG_JumpPressed	= 0x01,	// Jump pressed
	FLAG_WantsToCrouch	= 0x02,	// Wants to crouch
	FLAG_Reserved_1		= 0x04,	// Reserved for future use
	FLAG_Reserved_2		= 0x08,	// Reserved for future use
	// Remaining bit masks are available for custom flags.
	FLAG_Custom_0		= 0x10, // Sprinting
	FLAG_Custom_1		= 0x20,
	FLAG_Custom_2		= 0x40,
	FLAG_Custom_3		= 0x80,*/
	
	bIsSprinting = (Flags &= FSavedMove_Character::FLAG_Custom_0) != 0;
}

void USGCharacterMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
}

float USGCharacterMovementComponent::GetMaxSpeed() const
{
	float Result = Super::GetMaxSpeed();
	if(bIsSprinting)
	{
		Result = SprintSpeed;
	}

	return Result;
}

void USGCharacterMovementComponent::SetIsSprinting(bool NewState)
{
	bIsSprinting = NewState;
}

void USGCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(FMath::IsNearlyZero(Velocity.Size()) && bIsSprinting)
	{
		SetIsSprinting(false);
	}
}

void FSavedMove_SG::Clear()
{
	FSavedMove_Character::Clear();
	bSavedIsSprinting = 0;
}

uint8 FSavedMove_SG::GetCompressedFlags() const
{
	uint8 Result = Super::GetCompressedFlags();

	/*FLAG_JumpPressed	= 0x01,	// Jump pressed
	FLAG_WantsToCrouch	= 0x02,	// Wants to crouch
	FLAG_Reserved_1		= 0x04,	// Reserved for future use
	FLAG_Reserved_2		= 0x08,	// Reserved for future use
	// Remaining bit masks are available for custom flags.
	FLAG_Custom_0		= 0x10, // Sprinting
	FLAG_Custom_1		= 0x20,
	FLAG_Custom_2		= 0x40,
	FLAG_Custom_3		= 0x80,*/
	
	if(bSavedIsSprinting)
	{
		Result |= FLAG_Custom_0;
	}

	return Result;
}

bool FSavedMove_SG::CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const
{
	FSavedMove_SG* NewMoveSG = StaticCast<FSavedMove_SG*>(NewMove.Get());

	if(bSavedIsSprinting != NewMoveSG->bSavedIsSprinting)
	{
		return false;
	}

	return Super::CanCombineWith(NewMove, InCharacter, MaxDelta);
}

void FSavedMove_SG::SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel,
	FNetworkPredictionData_Client_Character& ClientData)
{
	Super::SetMoveFor(C, InDeltaTime, NewAccel, ClientData);

	const USGCharacterMovementComponent* SGCharacterMovementComponent = StaticCast<USGCharacterMovementComponent*>(C->GetCharacterMovement());

	bSavedIsSprinting = SGCharacterMovementComponent->bIsSprinting;
}

void FSavedMove_SG::PrepMoveFor(ACharacter* C)
{
	Super::PrepMoveFor(C);

	USGCharacterMovementComponent* SGCharacterMovementComponent = StaticCast<USGCharacterMovementComponent*>(C->GetCharacterMovement());

	SGCharacterMovementComponent->bIsSprinting = bSavedIsSprinting;
}

FNetworkPredictionData_Client_SGCharacter::FNetworkPredictionData_Client_SGCharacter(
	const UCharacterMovementComponent& ClientMovement) : Super(ClientMovement)
{
	
}

FSavedMovePtr FNetworkPredictionData_Client_SGCharacter::AllocateNewMove()
{
	return FSavedMovePtr(new FSavedMove_SG());
}
