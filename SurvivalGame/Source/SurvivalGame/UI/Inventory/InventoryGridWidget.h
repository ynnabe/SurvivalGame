// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "Components/CanvasPanel.h"
#include "Runtime\Engine\Classes\Slate\SlateBrushAsset.h"
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

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual FReply NativeOnPreviewKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USlateBrushAsset* SlateBrush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DragNDrop parameters")
	FLinearColor AvailableColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DragNDrop parameters")
	FLinearColor NotAvailableColor;

private:

	FIntPoint DraggedItemTopLeftTile;
	bool DrawDropLocation = false;

	void MousePositionInTile(FVector2d MousePosition, bool& Right, bool& Down) const;

	bool IsRoomAvailableForPayload(UInventoryItem* Payload) const;

	UInventoryItem* GetPayload(UDragDropOperation* DragDropOperation) const;

	UFUNCTION()
	void OnItemRemoved(UInventoryItem* ItemToRemove);
	
	void CreateLineSegments();

	void Refresh();

	TArray<FGridLine> Lines;

	UPROPERTY()
	USGInventoryComponent* CachedInventoryComponent;
};
