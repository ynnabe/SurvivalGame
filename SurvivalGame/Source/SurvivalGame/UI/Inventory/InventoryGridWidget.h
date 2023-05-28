// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "Components/CanvasPanel.h"
#include "InventoryGridWidget.generated.h"

class UItemWidget;
class UEquipmentWidget;
class UBorder;
class USGInventoryComponent;
class UGridPanel;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UInventoryGridWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void InitializeGrid(USGInventoryComponent* InventoryComponent, FVector2d& FinishSize);

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;


protected:

	UPROPERTY(meta=(BindWidget))
	UBorder* GridBorder;
	
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* GridCanvasPanel;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TileSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UItemWidget> ItemWidgetClass;

private:

	UFUNCTION()
	void OnItemRemoved(AItem* ItemToRemove);
	
	void CreateLineSegments();

	void Refresh();

	TArray<FGridLine> Lines;

	UPROPERTY()
	USGInventoryComponent* CachedInventoryComponent;
};
