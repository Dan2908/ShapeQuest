// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Constant.h"
#include "ShapedObjectBase.generated.h"

class USphereComponent;
class UShinyObject;

UCLASS()
class SHAPEQUEST_API AShapedObjectBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShapedObjectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Shaped Object")
	void SetItemType(const EShapeType Type) { ShapeType = Type; }

	UFUNCTION(BlueprintCallable, Category = "Shaped Object")
	const EShapeType GetItemType() const { return ShapeType; }

	// Set this object to shine or not
	UFUNCTION(BlueprintCallable, Category = "Shining")
	void SetShine(const bool Value);

	const bool ActorIsActivating(AActor* Actor);

private:
	/* Whether a proper actor is overlapping the activation(trigger) area
	* Using a single bool for optimization's sake, in case of multiple players this must be a object reference Array
	*/ 
	TArray<AActor*> ActorsActivating;

	static const FName ProperActorTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Object", meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EShapeType> ShapeType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Object", meta = (AllowPrivateAccess = "true"))
	UShinyObject* ShiningMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Object", meta = (AllowPrivateAccess = "true"))
	USphereComponent* TriggerArea;

	UFUNCTION()
	void OnActorOverlaps(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnActorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void HandleHiding();

};
