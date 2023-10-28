// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SlideDoor.generated.h"
		
class UMaterialInstanceDynamic;
class UShinyObject;

UCLASS()
class SHAPEQUEST_API ASlideDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASlideDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
	FLinearColor CubeActiveColor = FColor::Green;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
	FLinearColor SphereActiveColor = FColor::Red;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
	FLinearColor ConeActiveColor = FColor::Purple;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Slots")
	FLinearColor CylinderActiveColor = FColor::Blue;

private:

	//Mesh components
	UPROPERTY(EditDefaultsOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	UShinyObject* CubePlateMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	UShinyObject* SpherePlateMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	UShinyObject* ConePlateMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Door", meta = (AllowPrivateAccess = "true"))
	UShinyObject* CylinderPlateMesh;

};
