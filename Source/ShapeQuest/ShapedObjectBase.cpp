// Fill out your copyright notice in the Description page of Project Settings.


#include "ShapedObjectBase.h"

#include "Components/SphereComponent.h"
#include "ShinyObject.h"

#ifndef LOG_SIMPLE
	#define LOG_SIMPLE(x, ...) UE_LOG(LogTemp, Display, TEXT(x), __VA_ARGS__)
#endif

const FName AShapedObjectBase::ProperActorTag = "MainCharacter";

// Sets default values
AShapedObjectBase::AShapedObjectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShiningMesh = CreateDefaultSubobject<UShinyObject>(TEXT("Shape Mesh"));
	RootComponent = ShiningMesh;
	TriggerArea = CreateDefaultSubobject<USphereComponent>(TEXT("Trigger Box"));
	TriggerArea->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AShapedObjectBase::BeginPlay()
{
	Super::BeginPlay();

	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &AShapedObjectBase::OnActorOverlaps);
	TriggerArea->OnComponentEndOverlap.AddDynamic(this, &AShapedObjectBase::OnActorEndOverlap);
}

// Called every frame
void AShapedObjectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Activate if proper actor os overlapping, or backwards
	if(ActorsActivating.Num() > 0)
	{
		SetShine(true);
	}
	else
	{
		SetShine(false);
	}

	ShiningMesh->RefreshValues(DeltaTime);

}


void AShapedObjectBase::SetShine(const bool Value)
{
	ShiningMesh->SetShining(Value);
	ShiningMesh->SetActivated(Value);
}

const bool AShapedObjectBase::ActorIsActivating(AActor* Actor)
{
	for (const AActor* actor : ActorsActivating)
	{
		if (actor == Actor)
		{
			return true;
		}
	}
	return false;
}

void AShapedObjectBase::OnActorOverlaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(ProperActorTag))
	{
		ActorsActivating.Push(OtherActor);
		LOG_SIMPLE("Actor %s entered %s zone", *OtherActor->GetName(), *this->GetName());
	}
}

void AShapedObjectBase::OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag(ProperActorTag))
	{
		ActorsActivating.Remove(OtherActor);
		LOG_SIMPLE("Actor %s left %s zone", *OtherActor->GetName(), *this->GetName());
	}
}

void AShapedObjectBase::HandleHiding()
{
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}


