// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SGCharacterAttributesWidget.generated.h"

class ASGBaseCharacter;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API USGCharacterAttributesWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void BindDelegates(ASGBaseCharacter* OwnerCharacter);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Stamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Hungry;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes")
	float Hydration;

private:

	UFUNCTION()
	void UpdateHealth(float NewValue) { Health = NewValue; }

	UFUNCTION()
	void UpdateStamina(float NewValue) { Stamina = NewValue; }

	UFUNCTION()
	void UpdateHungry(float NewValue) { Hungry = NewValue; }

	UFUNCTION()
	void UpdateHydration(float NewValue) { Hydration = NewValue; }
};
