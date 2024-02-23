// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBaseCharacter.h"
#include "Controller/SGPlayerController.h"
#include "Net/UnrealNetwork.h"
#include "SurvivalGame/Actors/Items/Item.h"
#include "SurvivalGame/Components/Character/EquipmentComponent.h"
#include "SurvivalGame/Components/Character/SGCharacterAttributes.h"
#include "SurvivalGame/Components/Character/SGCharacterMovementComponent.h"
#include "SurvivalGame/Inventory/InventoryItem.h"


ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SGCharacterMovementComponent = Cast<USGCharacterMovementComponent>(GetCharacterMovement());
	SGCharacterAttributes = CreateDefaultSubobject<USGCharacterAttributes>(TEXT("CharacterAttributes"));
	SGEquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>(TEXT("EquipmentComponent"));

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

void ASGBaseCharacter::Interact()
{
	
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

void ASGBaseCharacter::SpawnDropedItem(UInventoryItem* ItemToSpawn)
{
	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = GetActorRotation();
	FActorSpawnParameters ActorSpawnParameters;
	GetWorld()->SpawnActor<AItem>(ItemToSpawn->GetItemActorClass(), SpawnLocation, SpawnRotation, ActorSpawnParameters);
}

void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<ASGPlayerController>(GetController());
}


void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

