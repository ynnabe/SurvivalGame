// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGCharacterAttributes.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVALGAME_API USGCharacterAttributes : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	USGCharacterAttributes();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FOnAttributeChangeSignature OnHealthChanged;
	FOnAttributeChangeSignature OnStaminaChanged;
	FOnAttributeChangeSignature OnHungryChanged;
	FOnAttributeChangeSignature OnHydrationChanged;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetHealth() const { return Health; }
	FORCEINLINE float GetMaxHealth() const { return MaxHealth; }
	void SetHealth(float NewValue);

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetStamina() const { return Stamina; }
	FORCEINLINE float GetMaxStamina() const { return MaxStamina; }
	void SetStamina(float NewValue);

	FORCEINLINE float GetHungry() const { return Hungry; }
	FORCEINLINE float GetMaxHungry() const { return MaxHungry; }
	void SetHungry(float NewValue);

	FORCEINLINE float GetHydration() const { return Hydration; }
	FORCEINLINE float GetMaxHydration() const { return MaxHydration; }
	void SetHydration(float NewValue);

	void SetCDStamina(bool NewValue) { bIsCDStamina = NewValue; }
	void SetIsSprinting(bool NewValue) { bIsSprinting = NewValue; }

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
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | Restore parameters")
	float RestoreStaminaValue = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | LostAttributes")
	float LostHydrationPerTime = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | LostAttributes")
	float LostHungryPerTime = 0.1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | LostAttributes")
	float LostTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Attributes parameters | LostAttributes")
	float LostStaminaSprinting = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Restore parameters")
	float RestoreStaminaCoolDown = 2.0f;
	
public:	
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CalculateAttributes();
	void HealthChanged();

	UPROPERTY(ReplicatedUsing=OnRep_HealthChanged)
	float Health = 0.0f;

	UFUNCTION()
	void OnRep_HealthChanged();
	void StaminaChanged();

	UPROPERTY(ReplicatedUsing=OnRep_StaminaChanged)
	float Stamina = 0.0f;

	UFUNCTION()
	void OnRep_StaminaChanged();
	void HungryChanged();

	UPROPERTY(ReplicatedUsing=OnRep_HungryChanged)
	float Hungry = 0.0f;

	UFUNCTION()
	void OnRep_HungryChanged();
	void HydrationChanged();

	UPROPERTY(ReplicatedUsing=OnRep_HydrationChanged)
	float Hydration = 0.0f;

	UFUNCTION()
	void OnRep_HydrationChanged();

	bool bIsCDStamina = false;

	UPROPERTY(Replicated)
	bool bIsSprinting = false;

	FTimerHandle LostAttributesPerSecondTimer;
	FTimerHandle SprintingTimer;
};
