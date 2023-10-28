// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHAPEQUEST_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void PickUp();

private:
	
	// Max distance around actor to trace for grabbable objects.
	UPROPERTY(EditDefaultsOnly, Category = "Tracing Properties", meta = (AllowPrivateAccess = "true"))
	float MaxGrabbingTrace = 150.0f;
	// Max distance around actor to trace for grabbable objects.
	UPROPERTY(EditDefaultsOnly, Category = "Tracing Properties", meta = (AllowPrivateAccess = "true"))
	float MaxGrabbingRange = 150.0f;
	// Returns true if the mouse is over an object that can be grabbed, false otherwise.
	UFUNCTION()
	const bool GetMouseOverGrabObject(FHitResult& MouseHitResult);


	ACharacter* Player;
	APlayerController* PlayerController;

};
