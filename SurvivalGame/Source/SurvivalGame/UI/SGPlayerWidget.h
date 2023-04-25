// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "SurvivalGame/UI/SGCharacterAttributesWidget.h"
#include "SurvivalGame/UI/InteractableWidget.h"
#include "SGPlayerWidget.generated.h"


/**
 * 
 */
UCLASS()
class SURVIVALGAME_API USGPlayerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	USGCharacterAttributesWidget* GetCharacterAttributesWidget() const { return WidgetTree->FindWidget<USGCharacterAttributesWidget>(CharacterAttributesWidgetName); }
	UInteractableWidget* GetCharacterInteractableWidget() const { return WidgetTree->FindWidget<UInteractableWidget>(CharacterInteractableWidgetName); }
	
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget names")
	FName CharacterAttributesWidgetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget names")
	FName CharacterInteractableWidgetName;
};
