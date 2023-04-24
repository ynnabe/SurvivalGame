// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGInteractableInterface.generated.h"

class ASGBaseCharacter;

UINTERFACE(MinimalAPI)
class USGInteractableInterface : public UInterface
{
	GENERATED_BODY()
};


class SURVIVALGAME_API ISGInteractableInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, Category="Interact")
	void DetectedByTraceInteract();
	
	virtual void InteractPure(ASGBaseCharacter* Character) PURE_VIRTUAL(ISGInteractableInterface::Interact);
};
