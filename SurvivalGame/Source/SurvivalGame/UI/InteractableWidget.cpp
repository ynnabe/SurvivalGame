// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableWidget.h"

#include "SurvivalGame/Character/SGPlayerCharacter.h"

void UInteractableWidget::BindDelegates(ASGPlayerCharacter* OwnerCharacter)
{
	OwnerCharacter->InteractableDetected.BindUObject(this, &UInteractableWidget::UpdateWidget);
}

void UInteractableWidget::UpdateWidget(bool VisibleState, FText InteractableText_In)
{
	InteractableText = InteractableText_In;
	if(VisibleState)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}
