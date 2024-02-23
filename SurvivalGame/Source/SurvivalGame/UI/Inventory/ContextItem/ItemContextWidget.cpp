// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemContextWidget.h"

#include "SurvivalGame/UI/Inventory/ItemWidget.h"

void UItemContextWidget::SetItem(UInventoryItem* ItemIn, UItemWidget* ItemWidgetIn)
{
	Item = ItemIn;
	ItemWidget = ItemWidgetIn;
}

void UItemContextWidget::RemoveItem()
{
	ItemWidget->RemoveItem();
	RemoveFromParent();
}
