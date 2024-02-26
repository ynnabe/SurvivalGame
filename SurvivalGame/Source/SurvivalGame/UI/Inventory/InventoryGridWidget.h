// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "Components/CanvasPanel.h"
#include "Runtime\Engine\Classes\Slate\SlateBrushAsset.h"
#include "InventoryGridWidget.generated.h"

class UUSGLinesDrawer;
class ASGPlayerController;
class ASGPlayerCharacter;
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
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UCanvasPanel* GetGridCanvasPanel() const { return GridCanvasPanel; }

	UBorder* GetGridBorder() const { return GridBorder; }
	bool GetDrawDropLocation() const { return DrawDropLocation; }
	UInventoryItem* GetPayload() const;
	UInventoryItem* GetPayload(UDragDropOperation* DragDropOperation) const;
	bool IsDraggingDrop() const { return UWidgetBlueprintLibrary::IsDragDropping(); }
	bool IsRoomAvailableForPayload(UInventoryItem* Payload) const;
	FIntPoint GetDraggedItemToLeftTile() const { return DraggedItemTopLeftTile; }


protected:

	UPROPERTY(meta=(BindWidget))
	UBorder* GridBorder;
	
	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* GridCanvasPanel;

	UPROPERTY(meta=(BindWidget))
	UUSGLinesDrawer* LinesDrawer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TileSize;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UItemWidget> ItemWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USlateBrushAsset* SlateBrush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USoundBase* DropSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DragNDrop parameters")
	FLinearColor AvailableColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="DragNDrop parameters")
	FLinearColor NotAvailableColor;

private:

	FIntPoint DraggedItemTopLeftTile;
	
	bool DrawDropLocation = false;

	void MousePositionInTile(FVector2d MousePosition, bool& Right, bool& Down) const;

	UFUNCTION()
	void OnItemRemoved(UInventoryItem* ItemToRemove, bool bNeedToDrop);
	
	void CreateLineSegments();

	void Refresh();

	TArray<FGridLine> Lines;

	UPROPERTY()
	USGInventoryComponent* CachedInventoryComponent;

	UPROPERTY()
	ASGPlayerCharacter* Player;

	UPROPERTY()
	ASGPlayerController* PlayerController;
};
