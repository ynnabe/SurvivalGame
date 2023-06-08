// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UCanvasPanel;
class USGInventoryComponent;
class UEquipmentWidget;
class UEquipmentItem;
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

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	void SetTorsoEquipmentWidget(UEquipmentItem* InventoryComponent);
	void SetBackpackEquipmentWidget(UEquipmentItem* InventoryComponent);

protected:

	UPROPERTY(meta=(BindWidget))
	UEquipmentWidget* TorsoEquipmentWidget;

	UPROPERTY(meta=(BindWidget))
	UEquipmentWidget* BackpackEquipmentWidget;
	
};
