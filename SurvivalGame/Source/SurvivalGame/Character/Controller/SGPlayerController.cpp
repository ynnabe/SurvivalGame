// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/Character/SGPlayerCharacter.h"
#include "SurvivalGame/UI/InteractableWidget.h"
#include "SurvivalGame/UI/SGCharacterAttributesWidget.h"
#include "SurvivalGame/UI/SGPlayerWidget.h"

void ASGPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	CachedBaseCharacter = Cast<ASGBaseCharacter>(InPawn);
	if(CachedBaseCharacter.IsValid() && IsLocalController())
	{
		CreateAndInitializeWidgets();
	}
}

void ASGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(GetLocalRole() == ROLE_Authority)
	{
		Client_SetupEI();
	}
}

void ASGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if(JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASGPlayerController::JumpPressed);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASGPlayerController::JumpReleased);
		}

		if(MovementAction)
		{
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASGPlayerController::Move);
		}
		
		if(LookAction)
		{
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASGPlayerController::Look);
		}

		if(SprintAction)
		{
			PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASGPlayerController::StartSprint);
			PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASGPlayerController::StopSprint);
		}

		if(InteractAction)
		{
			PlayerEnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ASGPlayerController::Interact);
		}
	}
}

void ASGPlayerController::Client_SetupEI_Implementation()
{
	if(APlayerController* PC = Cast<APlayerController>(this))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
		}

		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly {});
	}
}

void ASGPlayerController::Move(const FInputActionValue& Value)
{
	if(CachedBaseCharacter.IsValid())
	CachedBaseCharacter->Move(Value);
}

void ASGPlayerController::Look(const FInputActionValue& Value)
{
	if(CachedBaseCharacter.IsValid())
	CachedBaseCharacter->Look(Value);
}

void ASGPlayerController::JumpPressed()
{
	if(CachedBaseCharacter.IsValid())
	CachedBaseCharacter->Jump();
}

void ASGPlayerController::JumpReleased()
{
	if(CachedBaseCharacter.IsValid())
	CachedBaseCharacter->StopJumping();
}

void ASGPlayerController::StartSprint()
{
	if(CachedBaseCharacter.IsValid())
	CachedBaseCharacter->StartSprint();
}

void ASGPlayerController::StopSprint()
{
	if(CachedBaseCharacter.IsValid())
	CachedBaseCharacter->StopSprint();
}

void ASGPlayerController::Interact()
{
	if(CachedBaseCharacter.IsValid())
	CachedBaseCharacter->Interact();
}

void ASGPlayerController::CreateAndInitializeWidgets()
{
	if(!IsValid(PlayerHUDWidget))
	{
		PlayerHUDWidget = CreateWidget<USGPlayerWidget>(GetWorld(), PlayerHUDWidgetClass);
		if(IsValid(PlayerHUDWidget))
		{
			PlayerHUDWidget->AddToViewport();
		}
	}

	if(CachedBaseCharacter.IsValid() && IsValid((PlayerHUDWidget)))
	{
		USGCharacterAttributesWidget* AttributesWidget = PlayerHUDWidget->GetCharacterAttributesWidget();
		if(IsValid(AttributesWidget))
		{
			AttributesWidget->BindDelegates(CachedBaseCharacter.Get());
		}
	}

	if(CachedBaseCharacter.IsValid() && IsValid(PlayerHUDWidget))
	{
		UInteractableWidget* InteractableWidget = PlayerHUDWidget->GetCharacterInteractableWidget();
		if(IsValid(InteractableWidget))
		{
			InteractableWidget->BindDelegates(Cast<ASGPlayerCharacter>(CachedBaseCharacter.Get()));
		}
	}
}
