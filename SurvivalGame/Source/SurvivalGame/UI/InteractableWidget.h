// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractableWidget.generated.h"

class ASGPlayerCharacter;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UInteractableWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindDelegates(ASGPlayerCharacter* OwnerCharacter);

protected:

	void UpdateWidget(bool VisibleState, FText InteractableText_In);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	FText InteractableText;
};
