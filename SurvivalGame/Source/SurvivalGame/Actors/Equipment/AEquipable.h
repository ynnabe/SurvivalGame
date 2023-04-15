// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AEquipable.generated.h"

UCLASS()
class SURVIVALGAME_API AAEquipable : public AActor
{
	GENERATED_BODY()
	
public:
	AAEquipable();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
