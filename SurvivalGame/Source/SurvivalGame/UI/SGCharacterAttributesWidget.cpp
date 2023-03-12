// Fill out your copyright notice in the Description page of Project Settings.


#include "SGCharacterAttributesWidget.h"

#include "SurvivalGame/Character/SGBaseCharacter.h"
#include "SurvivalGame/Components/Character/SGCharacterAttributes.h"

void USGCharacterAttributesWidget::BindDelegates(ASGBaseCharacter* OwnerCharacter)
{
	USGCharacterAttributes* CharacterAttributes = OwnerCharacter->GetCharacterAttributes();
	CharacterAttributes->OnHealthChanged.AddUObject(this, &USGCharacterAttributesWidget::UpdateHealth);
	CharacterAttributes->OnStaminaChanged.AddUObject(this, &USGCharacterAttributesWidget::UpdateStamina);
	CharacterAttributes->OnHungryChanged.AddUObject(this, &USGCharacterAttributesWidget::UpdateHungry);
	CharacterAttributes->OnHydrationChanged.AddUObject(this, &USGCharacterAttributesWidget::UpdateHydration);
}
