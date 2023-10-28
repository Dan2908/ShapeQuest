// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "ShapedObjectBase.h"
#include "ShapeQuestCharacter.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	
	Player = Cast<ACharacter>(GetOwner());
	check(Player != nullptr);

	PlayerController = Cast<APlayerController>(Player->GetController());
	check(PlayerController != nullptr);
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGrabber::PickUp()
{
	FHitResult MouseHitResult;
	
	if (!GetMouseOverGrabObject(MouseHitResult))
	{
		return;
	}
	
	AShapedObjectBase* HitObject = Cast<AShapedObjectBase>(MouseHitResult.GetActor());

	if (HitObject->ActorIsActivating(GetOwner()))
	{
		// Grab
	}

}

const bool UGrabber::GetMouseOverGrabObject(FHitResult& MouseHitResult)
{
	// Only hits grabbable components by channel GrabbableTrace
	PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, false, MouseHitResult);

	if (MouseHitResult.bBlockingHit)
	{
		if (FVector::Dist(Player->GetActorLocation(), MouseHitResult.ImpactPoint) <= MaxGrabbingTrace)
		{
			return true;
		}
	}
	return false;
}

