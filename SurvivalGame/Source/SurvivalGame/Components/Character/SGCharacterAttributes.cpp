// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCharacterAttributes.h"

// Sets default values for this component's properties
USGCharacterAttributes::USGCharacterAttributes()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USGCharacterAttributes::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);
	SetStamina(MaxStamina);
	SetHungry(MaxHungry);
	SetHydration(MaxHydration);

	GetWorld()->GetTimerManager().SetTimer(LostAttributesPerSecondTimer, this, &USGCharacterAttributes::CalculateAttributes, LostTime, true, 1.0f);
}


// Called every frame
void USGCharacterAttributes::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USGCharacterAttributes::CalculateAttributes()
{
	SetHungry(Hungry - LostHungryPerTime);
	SetHydration(Hydration - LostHydrationPerTime);
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Hungry: %f"), GetHungry()));
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Hydration: %f"), GetHydration()));
}

