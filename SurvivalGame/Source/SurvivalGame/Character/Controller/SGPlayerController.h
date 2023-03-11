// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SGPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class SURVIVALGAME_API ASGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	virtual void SetPawn(APawn* InPawn) override;

	virtual void OnPossess(APawn* InPawn) override;
	
	virtual void SetupInputComponent() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input mapping")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input mapping")
	int32 BaseMappingPriority = 0;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();

private:

	TWeakObjectPtr<ASGBaseCharacter> CachedBaseCharacter;
	
};
