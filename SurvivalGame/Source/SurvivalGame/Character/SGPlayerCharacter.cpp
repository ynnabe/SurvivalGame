// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Controller/SGPlayerController.h"
#include "SurvivalGame/Actors/Items/Item.h"
#include "SurvivalGame/Components/Character/SGCharacterMovementComponent.h"
#include "SurvivalGame/Interfaces/SGInteractableInterface.h"
#include "SurvivalGame/UI/Inventory/InventoryWidget.h"

ASGPlayerCharacter::ASGPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh());
	CameraComponent->bUsePawnControlRotation = true;

	FPSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSkeletalMeshComponent"));
	FPSkeletalMeshComponent->SetupAttachment(RootComponent);
	FPSkeletalMeshComponent->SetOnlyOwnerSee(true);
	GetMesh()->SetCastHiddenShadow(true);
}

void ASGPlayerCharacter::CreateInventoryWidget()
{
	InventoryWidget = CreateWidget<UInventoryWidget>(GetPlayerController(), InventoryWidgetClass);
}

void ASGPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CreateInventoryWidget();
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

void ASGPlayerCharacter::Interact()
{
	Super::Interact();

	if(IsValid(InteractableLineObject))
	{
		ISGInteractableInterface* Interface = Cast<ISGInteractableInterface>(InteractableLineObject);
		if(Interface)
		{
			Interface->InteractPure(this);
		}
	}
}

void ASGPlayerCharacter::UseInventory()
{
	Super::UseInventory();

	if(!IsValid(InventoryWidget))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("InventoryWidget is not vaild!")));
		return;
	}

	if(InventoryWidget->IsVisible())
	{
		InventoryWidget->RemoveFromParent();
		GetPlayerController()->Client_ToggleInventoryMapping(false);
		GetPlayerController()->GetPlayerWidget()->AddToViewport();
	}
	else
	{
		InventoryWidget->AddToViewport();
		GetPlayerController()->Client_ToggleInventoryMapping(true);
		GetPlayerController()->GetPlayerWidget()->RemoveFromParent();
	}

}

void ASGPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FHitResult InteractableHitResult;
	FVector ViewLocation;
	FRotator ViewRotation;
	GetController()->GetPlayerViewPoint(ViewLocation, ViewRotation);
	FVector StartTrace = ViewRotation.Vector();
	FVector EndTrace = ViewLocation + StartTrace * InteractTraceLength;
	
	if(GetWorld()->LineTraceSingleByChannel(InteractableHitResult, ViewLocation, EndTrace, ECC_Visibility))
	{
		if(InteractableLineObject != InteractableHitResult.GetActor())
		{
			if(ISGInteractableInterface* Interface = Cast<ISGInteractableInterface>(InteractableLineObject))
			{
				Interface->Execute_DetectedByTraceInteract(InteractableLineObject);
			}
			if(ISGInteractableInterface* Interface = Cast<ISGInteractableInterface>(InteractableHitResult.GetActor()))
			{
				InteractableLineObject = InteractableHitResult.GetActor();
				Interface->Execute_DetectedByTraceInteract(InteractableLineObject);
				if(AItem* Item = Cast<AItem>(InteractableLineObject))
				{
					InteractableDetected.Execute(true, Item->GetItemName());
				}
			}
			else
			{
				InteractableLineObject = nullptr;
				InteractableDetected.Execute(false, FText());
			}
		}
	}
	else
	{
		if(ISGInteractableInterface* Interface = Cast<ISGInteractableInterface>(InteractableLineObject))
		{
			Interface->Execute_DetectedByTraceInteract(InteractableLineObject);
		}

		InteractableLineObject = nullptr;
		InteractableDetected.Execute(false, FText());
	}
}

void ASGPlayerCharacter::OnStopSprint_Implementation()
{
}

void ASGPlayerCharacter::OnStartSprint_Implementation()
{
}
