// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShapeQuestGameMode.generated.h"

UCLASS(minimalapi)
class AShapeQuestGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShapeQuestGameMode();

	virtual void BeginPlay() override;

	//UFUNCTION(BlueprintImplementableEvent)
	//void StartGame() {}

private:

	class AShapeQuestController* PlayerController;

	class AShapeQuestCharacter* MainPlayer;


};



