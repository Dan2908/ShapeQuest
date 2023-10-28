// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShinyObject.generated.h"

#ifndef LOG_SIMPLE
	#define LOG_SIMPLE(x, ...) UE_LOG(LogTemp, Display, TEXT(x), __VA_ARGS__)
#endif

UCLASS()
class SHAPEQUEST_API UShinyObject : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties.
	UShinyObject();

protected:
	// Called when the game starts.
	virtual void BeginPlay() override;

public:	
	// Call this function in parent's tick event to check and refresh values over time.
	inline void RefreshValues(const float DeltaValue) 
	{ 
		// For the moment check if its not Enabling/Disabling before switch activated
		if (!ShouldShiningRefresh(DeltaValue * ShineFadingSpeed * MaxBloomValue))
		{
			ShouldColorRefresh(DeltaValue * ActiveFadingSpeed);
		}
	}

	// Change default color to fade to when activated.
	UFUNCTION()
	inline void SetDefaultActiveColor(const FLinearColor& NewColor) { DefaultActiveColor = NewColor; }
	// Enable or disable the shining.
	UFUNCTION()
	inline void SetShining(const bool Value) { bShining = Value; }
	// Activate or deactivate this object (meaning color White or DefaultActiveColor).
	UFUNCTION()
	inline void SetActivated(const bool Value) { bActivated = Value; }

private:
	// Custom material parameter names.
	static const FName BloomParameterName;
	static const FName ColorParameterName;

	UMaterialInstanceDynamic* MaterialDynamic;
	FLinearColor mColor;
	float mBloom;

	// How fast this mesh shining fades from zero to MaxBloomValue and viceversa.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shining Properties", meta = (AllowPrivateAccess = "true"))
	float ShineFadingSpeed = 1.0f;
	// How fast this mesh Color changes from White to DefaultActiveColor or viceversa.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shining Properties", meta = (AllowPrivateAccess = "true"))
	float ActiveFadingSpeed = 1.0f;
	// If true, this component increases it's material emissive from 0 to MaxBloomValue. The other way around if false.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shining Properties", meta = (AllowPrivateAccess = "true"))
	bool bShining = false;
	// If true, this component fades it's material color (tint) from White to DefaultActiveColor. The other way around if false.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shining Properties", meta = (AllowPrivateAccess = "true"))
	bool bActivated = false;
	// Max bloom value for shinning, the highest the most emissive.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shining Properties", meta = (AllowPrivateAccess = "true"))
	float MaxBloomValue = 100.0f;
	// Default Color to tint when activated.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shining Properties", meta = (AllowPrivateAccess = "true"))
	FLinearColor DefaultActiveColor = FColor::Red;

	// Check if its currently going Enabled.
	inline const bool IsEnabling() { return (bShining && mBloom < MaxBloomValue); }
	// Check if its currently going Disabled.
	inline const bool IsDisabling() { return (!bShining && mBloom > 0.0f); }
	// Check if its currently going Activated.
	inline const bool IsActivating() { return (bActivated && !mColor.Equals(DefaultActiveColor, 0.01)); }
	// Check if its currently going Deactivated.
	inline const bool IsDeactivating() { return (!bActivated && !mColor.Equals(FLinearColor::White, 0.01)); }

	// Makes the internal caclulations over bloom if its going Enabled/Disabled. Returns true if there was a refresh, false if nothing changed.
	inline const bool ShouldShiningRefresh(const float Calculated)
	{
		if (IsEnabling() || IsDisabling())
		{
			mBloom += (bShining ? Calculated : -Calculated);
			FMath::Clamp(mBloom, 0, MaxBloomValue);

			MaterialDynamic->SetScalarParameterValue(BloomParameterName, mBloom);
			return true;
		}
		return false;
	}
	// Makes the internal caclulations over color if its going Activated/Deactivated. Returns true if there was a refresh, false if nothing changed.
	inline const bool ShouldColorRefresh(const float Calculated)
	{
		if (IsActivating() || IsDeactivating())
		{
			if (bActivated)
			{
				mColor = FLinearColor::LerpUsingHSV(mColor, DefaultActiveColor, Calculated);
			}
			else
			{
				mColor = FLinearColor::LerpUsingHSV(mColor, FLinearColor::White, Calculated);
			}

			MaterialDynamic->SetVectorParameterValue(ColorParameterName, mColor);
			return true;
		}
		return false;
	}
};
