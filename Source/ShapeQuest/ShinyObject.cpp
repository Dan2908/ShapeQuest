// Fill out your copyright notice in the Description page of Project Settings.


#include "ShinyObject.h"

const FName UShinyObject::BloomParameterName = "BloomValue";
const FName UShinyObject::ColorParameterName = "Tint";

// Sets default values for this component's properties
UShinyObject::UShinyObject()
{
}


// Called when the game starts
void UShinyObject::BeginPlay()
{
	Super::BeginPlay();

	MaterialDynamic = CreateAndSetMaterialInstanceDynamic(0);
	check(MaterialDynamic);
	// Set initial material parameters
	MaterialDynamic->SetScalarParameterValue(BloomParameterName, (bShining ? MaxBloomValue : 0));
	MaterialDynamic->SetVectorParameterValue(ColorParameterName, (bActivated ? DefaultActiveColor : FLinearColor::White));
}

