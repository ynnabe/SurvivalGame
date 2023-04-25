// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SGBaseCharacter.h"
#include "SurvivalGame/Interfaces/SGInteractableInterface.h"
#include "SGPlayerCharacter.generated.h"

DECLARE_DELEGATE_TwoParams(FInteractableDetectedSignature, bool, FText);
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API ASGPlayerCharacter : public ASGBaseCharacter
{
	GENERATED_BODY()

public:

	ASGPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	FInteractableDetectedSignature InteractableDetected;

	virtual void Move(const FInputActionValue& Value) override;
	virtual void Look(const FInputActionValue& Value) override;

	virtual void StartSprint() override;
	virtual void StopSprint() override;

	virtual void Interact() override;

	virtual void Tick(float DeltaSeconds) override;
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interactable parameters")
	float InteractTraceLength = 300.0f;
	
	UFUNCTION(BlueprintNativeEvent)
	void OnStartSprint();

	UFUNCTION(BlueprintNativeEvent)
	void OnStopSprint();

private:

	UPROPERTY()
	AActor* InteractableLineObject;
};
