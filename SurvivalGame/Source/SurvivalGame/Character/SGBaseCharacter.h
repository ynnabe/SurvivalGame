// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SGBaseCharacter.generated.h"

UCLASS()
class SURVIVALGAME_API ASGBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASGBaseCharacter();

	virtual void Move(const FInputActionValue& Value) {};
	virtual void Look(const FInputActionValue& Value) {};

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
