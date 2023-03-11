// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBaseCharacter.h"


ASGBaseCharacter::ASGBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}


void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASGBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

