// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SGPlayerController.generated.h"

class UItemContextWidget;
class USGPlayerWidget;
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

	FORCEINLINE USGPlayerWidget* GetPlayerWidget() const { return PlayerHUDWidget; }

	UFUNCTION(Client, Reliable)
	void Client_SetupEI();

	UFUNCTION(Client, Reliable)
	void Client_ToggleInventoryMapping(bool State);

	void SetItemContextWidget(UItemContextWidget* Widget);

	void ClearWidgets();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* InteractAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input actions")
	UInputAction* Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input mapping")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input mapping")
	int32 BaseMappingPriority = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Controls|Input mapping")
	UInputMappingContext* InventoryMappingContext;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();
	void StartSprint();
	void StopSprint();
	void Interact();
	void UseInventory();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widgets")
	TSubclassOf<USGPlayerWidget> PlayerHUDWidgetClass;

private:

	void CreateAndInitializeWidgets();

	UPROPERTY()
	USGPlayerWidget* PlayerHUDWidget = nullptr;

	UPROPERTY()
	UItemContextWidget* ItemContextWidget;

	TWeakObjectPtr<ASGBaseCharacter> CachedBaseCharacter;
	
};
