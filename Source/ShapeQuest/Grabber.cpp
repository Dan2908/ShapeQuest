// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "ShapedObjectBase.h"
#include "ShapeQuestCharacter.h"

#ifndef LOG_SIMPLE
	#define LOG_SIMPLE(x, ...) UE_LOG(LogTemp, Display, TEXT(x), __VA_ARGS__)
#endif


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

	// Get casted character
	Player = Cast<AShapeQuestCharacter>(GetOwner());
	check(Player != nullptr);

	PlayerController = Cast<APlayerController>(Player->GetController());
	check(PlayerController != nullptr);
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (IsGrabbing())
	{
		FVector Location, Direction;
		PlayerController->DeprojectMousePositionToWorld(Location, Direction);

		FVector TargetLocation = (Player->GetActorLocation() + Direction * HoldRange);

		Player->GetPhysicsHandle()->SetTargetLocation(TargetLocation);
	}
}


void UGrabber::PickUp()
{
	FHitResult MouseHitResult;
	
	if (!GetMouseOverGrabObject(MouseHitResult))
	{
		return;
	}

	AShapedObjectBase* HitActor = Cast<AShapedObjectBase>(MouseHitResult.GetActor());

	if (HitActor->ActorIsActivating(GetOwner()))
	{
		GrabbedComponent = MouseHitResult.GetComponent();
		if (GrabbedComponent)
		{
			GrabComponent();
		}
	}

}

void UGrabber::LetGo()
{
	ReleaseComponent();
	GrabbedComponent = nullptr;
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

void UGrabber::GrabComponent()
{
	UPhysicsHandleComponent* PhysicsHandle = Player->GetPhysicsHandle();
	check(PhysicsHandle);

	GrabbedComponent->WakeAllRigidBodies();
	GrabbedComponent->SetSimulatePhysics(true);
	// Fix SpringArm
	auto SpringArm = Player->GetCameraBoom();
	SpringArm->bUsePawnControlRotation = false;

	PhysicsHandle->GrabComponentAtLocationWithRotation(GrabbedComponent, NAME_None, GrabbedComponent->GetComponentLocation(), GrabbedComponent->GetComponentRotation());
}

void UGrabber::ReleaseComponent()
{
	// No need to check since when grabbed UPhysicsHandleComponent is already checked.
	UPhysicsHandleComponent* PhysicsHandle = Player->GetPhysicsHandle();

	// Unfix SpringArm
	auto SpringArm = Player->GetCameraBoom();
	SpringArm->bUsePawnControlRotation = true;

	PhysicsHandle->ReleaseComponent();
}

