// Fill out your copyright notice in the Description page of Project Settings.


#include "USGLinesDrawer.h"

#include "InventoryGridWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Kismet/KismetMathLibrary.h"
#include "SurvivalGame/Components/Inventory/Data/InventoryTypes.h"
#include "SurvivalGame/Inventory/InventoryItem.h"

int32 UUSGLinesDrawer::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry,
                                   const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId,
                                   const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	for (auto Line : Lines)
	{
		UBorder* Border = InventoryGridWidget->GetGridBorder();
		FVector2d LocalTopLeft = USlateBlueprintLibrary::GetLocalTopLeft(Border->GetCachedGeometry());
		FVector2d PositionA = Line.StartPoint + LocalTopLeft;
		FVector2d PositionB = Line.EndPoint + LocalTopLeft;
		FPaintContext PaintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle, bParentEnabled);
		UWidgetBlueprintLibrary::DrawLine(PaintContext, PositionA, PositionB, FLinearColor::White, true, 1.0f);
	}

	if(InventoryGridWidget->IsDraggingDrop() && InventoryGridWidget->GetDrawDropLocation())
	{
		UInventoryItem* Payload = InventoryGridWidget->GetPayload();
		if(IsValid(Payload))
		{
			int32 NewLayerId = LayerId + 1;
			if(InventoryGridWidget->IsRoomAvailableForPayload(Payload))
			{
				FPaintContext PaintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, NewLayerId, InWidgetStyle, bParentEnabled);
				FVector2d Position = UKismetMathLibrary::Conv_IntPointToVector2D(InventoryGridWidget->GetDraggedItemToLeftTile()) * TileSize;
				FVector2d Size = FVector2d(Payload->GetItemDimensions().X * TileSize, Payload->GetItemDimensions().Y * TileSize);
				UWidgetBlueprintLibrary::DrawBox(PaintContext, Position, Size, SlateBrush, AvailableColor);
			}
			else
			{
				FPaintContext PaintContext = FPaintContext(AllottedGeometry, MyCullingRect, OutDrawElements, NewLayerId, InWidgetStyle, bParentEnabled);
				FVector2d Position = UKismetMathLibrary::Conv_IntPointToVector2D(InventoryGridWidget->GetDraggedItemToLeftTile()) * TileSize;
				FVector2d Size = FVector2d(Payload->GetItemDimensions().X * TileSize, Payload->GetItemDimensions().Y * TileSize);
				UWidgetBlueprintLibrary::DrawBox(PaintContext, Position, Size, SlateBrush, NotAvailableColor);
			}
		}
	}
	
	return Super::NativePaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                          bParentEnabled);
}

void UUSGLinesDrawer::CreateLineSegments(int32 Columns, int32 Rows, float TileSize_In)
{
	for(int VerticalLine = 0; VerticalLine <= Columns; VerticalLine++)
	{
		int X = VerticalLine * TileSize_In;
		FVector2d StartLine = FVector2d(X, 0.0f);
		FVector2d EndLine = FVector2d(X, Rows * TileSize_In);
		FGridLine GridLine(StartLine, EndLine);
		Lines.Add(GridLine);
	}

	for(int HorizontalLine = 0; HorizontalLine <= Rows; HorizontalLine++)
	{
		int Y = HorizontalLine * TileSize_In;
		FVector2d StartLine = FVector2d(0.0f, Y);
		FVector2d EndLine = FVector2d(Columns * TileSize_In, Y);
		FGridLine GridLine(StartLine, EndLine);
		Lines.Add(GridLine);
	}

	TileSize = TileSize_In;
}
