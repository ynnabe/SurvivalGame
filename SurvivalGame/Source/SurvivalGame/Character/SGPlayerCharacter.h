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

	ASGPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

	virtual void StartSprint() override;
	virtual void StopSprint() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UCameraComponent* CameraComponent;

	
	UFUNCTION(BlueprintNativeEvent)
	void OnStartSprint();

	UFUNCTION(BlueprintNativeEvent)
	void OnStopSprint();

private:

	
};
