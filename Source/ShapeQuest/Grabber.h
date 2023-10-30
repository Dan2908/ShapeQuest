// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"

class AShapeQuestCharacter;

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
	// Call this function to pickup reachable objects
	UFUNCTION()
	void PickUp();
	// Call this function to release the already picked object.
	UFUNCTION()
	void LetGo();

	inline const bool IsGrabbing() { return GrabbedComponent != nullptr; }

private:
	
	// Max distance around actor to trace for grabbable objects.
	UPROPERTY(EditDefaultsOnly, Category = "Tracing Properties", meta = (AllowPrivateAccess = "true"))
	float MaxGrabbingTrace = 150.0f;
	// Max distance around actor to trace for grabbable objects.
	UPROPERTY(EditDefaultsOnly, Category = "Tracing Properties", meta = (AllowPrivateAccess = "true"))
	float HoldRange = 100.0f;
	// Returns true if the mouse is over an object that can be grabbed, false otherwise.
	UFUNCTION()
	const bool GetMouseOverGrabObject(FHitResult& MouseHitResult);
	//Handles logic to physically grab a component.
	UFUNCTION()
	void GrabComponent();
	//Handles logic to release object.
	UFUNCTION()
	void ReleaseComponent();

	AShapeQuestCharacter* Player;
	APlayerController* PlayerController;

	// Pointer to grabbed component. nullptr indicates no grabbing
	UPrimitiveComponent* GrabbedComponent;

};
