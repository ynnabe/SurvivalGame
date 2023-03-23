// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCharacterAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"

void USGCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CachedBaseCharacter = Cast<ASGBaseCharacter>(TryGetPawnOwner());
}

void USGCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(!CachedBaseCharacter.IsValid())
	{
		return;
	}

	Speed = CachedBaseCharacter->GetCharacterMovement()->Velocity.Size();
	Direction = UKismetAnimationLibrary::CalculateDirection(CachedBaseCharacter->GetCharacterMovement()->Velocity, CachedBaseCharacter->GetActorRotation());
	bIsJumping = CachedBaseCharacter->bIsJumping;
}
