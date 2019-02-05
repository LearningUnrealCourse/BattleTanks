// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Turret.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

	//Will move the barrel at a relative speed being -1 max downward and 1 max upward
	void Rotate(float RelativeSpeed);

private:

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5.f;
};
