// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/UI/SGCharacterAttributesWidget.h"
#include "SurvivalGame/UI/SGPlayerWidget.h"

void ASGPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	CachedBaseCharacter = Cast<ASGBaseCharacter>(InPawn);
	if(CachedBaseCharacter.IsValid())
	{
		CreateAndInitializeWidgets();
	}
}

void ASGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(APlayerController* PC = Cast<APlayerController>(this))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
		}
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
	}
}

void ASGPlayerController::Move(const FInputActionValue& Value)
{
	CachedBaseCharacter->Move(Value);
}

void ASGPlayerController::Look(const FInputActionValue& Value)
{
	CachedBaseCharacter->Look(Value);
}

void ASGPlayerController::JumpPressed()
{
	CachedBaseCharacter->Jump();
}

void ASGPlayerController::JumpReleased()
{
	CachedBaseCharacter->StopJumping();
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
}
