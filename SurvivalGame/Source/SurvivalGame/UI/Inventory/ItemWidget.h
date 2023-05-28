// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemWidget.generated.h"

class USlateBrushAsset;
class USizeBox;
class UBorder;
class UImage;
class AItem;

DECLARE_DELEGATE_OneParam(FOnRemovedSignature, AItem* Item);
/**
 * 
 */
UCLASS()
class SURVIVALGAME_API UItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	FOnRemovedSignature OnRemoved;
	
	virtual void NativeOnInitialized() override;

	void Refresh();

	void SetItemIcon();

	void SetItem(AItem* ItemIn);
	void SetTileSize(float TileSizeIn);

protected:

	UPROPERTY(meta=(BindWidget))
	USizeBox* BackgroundSizeBox;

	UPROPERTY(meta=(BindWidget))
	UBorder* BackgroundBorder;

	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

private:

	UPROPERTY()
	AItem* Item;

	FVector2d Size;

	FTimerHandle InitializeTimerHandle;
	
	float TileSize;
};
