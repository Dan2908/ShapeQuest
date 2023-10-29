// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapeQuestController.h"

void AShapeQuestController::BeginPlay()
{
	Super::BeginPlay();

	// Set Mouse cursor what we want
	CurrentMouseCursor = EMouseCursor::Crosshairs;
	// Show cursor.
	SetShowMouseCursor(true);
}
