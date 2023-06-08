// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipmentWidget.generated.h"

class UEquipmentItem;
class USGInventoryComponent;
class UInventoryGridWidget;
class UTextBlock;
class UImage;
class UInventorySlotWidget;
class UGridPanel;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	
	void OnSetEquipment(UEquipmentItem* NewEquipment, FVector2d& FinishSize);

protected:

	UPROPERTY(meta=(BindWidget))
	UInventoryGridWidget* GridWidget;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* EquipmentName;

	UPROPERTY(meta=(BindWidget))
	UImage* EquipmentImage;
};
