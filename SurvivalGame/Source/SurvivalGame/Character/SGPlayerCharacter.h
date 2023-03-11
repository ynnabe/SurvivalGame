// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGBaseCharacter.h"
#include "SGPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ASGPlayerCharacter : public ASGBaseCharacter
{
	GENERATED_BODY()

public:

	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;
	
};
