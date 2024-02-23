// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalGame/UI/Inventory/ItemWidget.h"
#include "ItemContextWidget.generated.h"

class UItemWidget;
class UButton;
class UInventoryItem;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UItemContextWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetItem(UInventoryItem* ItemIn, UItemWidget* ItemWidgetIn);

protected:

	UPROPERTY()
	UInventoryItem* Item;

	UPROPERTY()
	UItemWidget* ItemWidget;

	UPROPERTY(meta=(BindWidget))
	UButton* InspectButton;

	UPROPERTY(meta=(BindWidget))
	UButton* RemoveButton;

private:

	UFUNCTION(BlueprintCallable)
	void RemoveItem();
	
};
