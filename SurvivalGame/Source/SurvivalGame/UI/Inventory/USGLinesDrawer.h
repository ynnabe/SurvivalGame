// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "USGLinesDrawer.generated.h"

class USlateBrushAsset;
class UInventoryGridWidget;
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UUSGLinesDrawer : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual int32 NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const override;

	void CreateLineSegments(int32 Columns, int32 Rows, float TileSize);
	void SetInventoryGridWidget(UInventoryGridWidget* NewInventoryGridWidget) { InventoryGridWidget = NewInventoryGridWidget; }

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USlateBrushAsset* SlateBrush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DragNDrop parameters")
	FLinearColor AvailableColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DragNDrop parameters")
	FLinearColor NotAvailableColor;


private:
	float TileSize;

	UPROPERTY()
	UInventoryGridWidget* InventoryGridWidget;

	TArray<FGridLine> Lines;
};
