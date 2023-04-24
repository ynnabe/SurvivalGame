// Fill out your copyright notice in the Description page of Project Settings.


#include "SGInventoryComponent.h"

USGInventoryComponent::USGInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USGInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for(int Height = 0; Height < HeightSlots; Height++)
	{
		FInventoryRow InventoryRow;
		
		for(int Wight = 0; Wight < WidthSlots; Wight++)
		{
			InventoryRow.Row.Add(FInventorySlot());
		}
		InventorySlots.Add(Height, InventoryRow);
	}
}

void USGInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

