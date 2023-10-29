// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShapeQuestGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "ShapeQuestCharacter.h"
#include "ShapeQuestController.h"
#include "UObject/ConstructorHelpers.h"

AShapeQuestGameMode::AShapeQuestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AShapeQuestGameMode::BeginPlay()
{
	Super::BeginPlay();

	MainPlayer = Cast<AShapeQuestCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	PlayerController = Cast<AShapeQuestController>(UGameplayStatics::GetPlayerController(this, 0));

}
