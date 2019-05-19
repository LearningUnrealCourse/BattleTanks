// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	//Will move the barrel at a relative speed being -1 max downward and 1 max upward
	void Elevate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxDegreesPerSecond = 10.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MaxElevationDegrees = 40.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
	float MinElevationDegrees = 0.f;
};
