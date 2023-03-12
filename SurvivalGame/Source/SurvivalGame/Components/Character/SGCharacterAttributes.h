// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGCharacterAttributes.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API USGCharacterAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USGCharacterAttributes();

	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	void SetHealth(float NewValue) { Health = NewValue; }

	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	void SetStamina(float NewValue) { Stamina = NewValue; }

	FORCEINLINE float GetHungry() const { return Hungry; }
	FORCEINLINE float GetMaxHungry() const { return MaxHungry; }
	void SetHungry(float NewValue) { Hungry = NewValue; }

	FORCEINLINE float GetHydration() const { return Hydration; }
	FORCEINLINE float GetMaxHydration() const { return MaxHydration; }
	void SetHydration(float NewValue) { Hydration = NewValue; }

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters")
	float MaxHealth = 100.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters")
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters")
	float MaxHungry = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters")
	float MaxHydration = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | LostAttributes")
	float LostHydrationPerTime = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | LostAttributes")
	float LostHungryPerTime = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | LostAttributes")
	float LostTime = 1.0f;
	
public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CalculateAttributes();

	UPROPERTY()
	float Health = 0.0f;

	UPROPERTY()
	float Stamina = 0.0f;

	UPROPERTY()
	float Hungry = 0.0f;

	UPROPERTY()
	float Hydration = 0.0f;

	FTimerHandle LostAttributesPerSecondTimer;
};
