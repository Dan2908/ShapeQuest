// Fill out your copyright notice in the Description page of Project Settings.


#include "SlideDoor.h"
#include "ShinyObject.h"


// Sets default values
ASlideDoor::ASlideDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	RootComponent = DoorMesh;

	CubePlateMesh = CreateDefaultSubobject<UShinyObject>(TEXT("Cube Plate Mesh"));
	CubePlateMesh->SetupAttachment(RootComponent);
	SpherePlateMesh = CreateDefaultSubobject<UShinyObject>(TEXT("Sphere Plate Mesh"));
	SpherePlateMesh->SetupAttachment(RootComponent);
	ConePlateMesh = CreateDefaultSubobject<UShinyObject>(TEXT("Cone Plate Mesh"));
	ConePlateMesh->SetupAttachment(RootComponent);
	CylinderPlateMesh = CreateDefaultSubobject<UShinyObject>(TEXT("Cylinder Plate Mesh"));
	CylinderPlateMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASlideDoor::BeginPlay()
{
	Super::BeginPlay();

	CubePlateMesh->SetDefaultActiveColor(CubeActiveColor);
	SpherePlateMesh->SetDefaultActiveColor(SphereActiveColor);
	ConePlateMesh->SetDefaultActiveColor(ConeActiveColor);
	CylinderPlateMesh->SetDefaultActiveColor(CylinderActiveColor);
}

// Called every frame
void ASlideDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CubePlateMesh->RefreshValues(DeltaTime);
	SpherePlateMesh->RefreshValues(DeltaTime);
	ConePlateMesh->RefreshValues(DeltaTime);
	CylinderPlateMesh->RefreshValues(DeltaTime);
}