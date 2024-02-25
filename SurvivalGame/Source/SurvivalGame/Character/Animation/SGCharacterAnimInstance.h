// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SGCharacterAnimInstance.generated.h"

class ASGBaseCharacter;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API USGCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void ToggleFalling(bool NewState) { bIsJumping = NewState; }

	void SetSprinting(bool NewState) { bIsSprinting = NewState; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	float Speed;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	float Direction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	bool bIsJumping;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Parameters")
	bool bIsSprinting;

private:

	TWeakObjectPtr<ASGBaseCharacter> CachedBaseCharacter;
};
