// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class UInventoryItem;
class USlateBrushAsset;
class USizeBox;
class UBorder;
class UImage;
class AItem;

DECLARE_DELEGATE_OneParam(FOnRemovedSignature, UInventoryItem* Item);
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FOnRemovedSignature OnRemoved;

	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	
	virtual void NativeOnInitialized() override;

	void Refresh();

	void SetItemIcon();

	void SetItem(UInventoryItem* ItemIn);
	void SetTileSize(float TileSizeIn);

protected:

	UPROPERTY(meta=(BindWidget))
	USizeBox* BackgroundSizeBox;

	UPROPERTY(meta=(BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hover parameters")
	FLinearColor HoverColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Hover parameters")
	FLinearColor UnhoverColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Refresh parameters")
	float RefreshDelay = 0.5f;

private:

	UPROPERTY()
	UInventoryItem* Item;

	FVector2d Size;

	FTimerHandle InitializeTimerHandle;
	
	float TileSize;
};
