// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class USGInventoryComponent;
class UEquipmentWidget;
class UInventoryGridWidget;
class ASGPlayerCharacter;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void SetTorsoEquipmentWidget(USGInventoryComponent* InventoryComponent);
	void SetBackpackEquipmentWidget(USGInventoryComponent* InventoryComponent);

protected:

	UPROPERTY(meta=(BindWidget))
	UEquipmentWidget* TorsoEquipmentWidget;

	UPROPERTY(meta=(BindWidget))
	UEquipmentWidget* BackpackEquipmentWidget;
	
};
