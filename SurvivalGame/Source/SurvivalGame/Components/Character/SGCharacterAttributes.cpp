// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCharacterAttributes.h"

#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
USGCharacterAttributes::USGCharacterAttributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);

	// ...
}

void USGCharacterAttributes::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USGCharacterAttributes, Health);
	DOREPLIFETIME(USGCharacterAttributes, Stamina);
	DOREPLIFETIME(USGCharacterAttributes, Hungry);
	DOREPLIFETIME(USGCharacterAttributes, Hydration);
}

void USGCharacterAttributes::SetHealth(float NewValue)
{
	Health = NewValue;
	OnHealthChanged.Broadcast(Health / MaxHealth);
}

void USGCharacterAttributes::SetStamina(float NewValue)
{
	Stamina = NewValue;
	OnStaminaChanged.Broadcast(Stamina / MaxStamina);
}

void USGCharacterAttributes::SetHungry(float NewValue)
{
	Hungry = NewValue;
	OnHungryChanged.Broadcast(Hungry);
}

void USGCharacterAttributes::SetHydration(float NewValue)
{
	Hydration = NewValue;
	OnHydrationChanged.Broadcast(Hydration);
}

void USGCharacterAttributes::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	SetStamina(MaxStamina);
	SetHungry(MaxHungry);
	SetHydration(MaxHydration);

	GetWorld()->GetTimerManager().SetTimer(LostAttributesPerSecondTimer, this, &USGCharacterAttributes::CalculateAttributes, LostTime, true, 1.0f);
}


void USGCharacterAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Stamina != 100.0f && !bIsCDStamina)
	{
		SetStamina(FMath::Clamp(Stamina + RestoreStaminaValue * DeltaTime, 0.0f, MaxStamina));
	}
}

void USGCharacterAttributes::CalculateAttributes()
{
	SetHungry(Hungry - LostHungryPerTime);
	SetHydration(Hydration - LostHydrationPerTime);
}

