// Fill out your copyright notice in the Description page of Project Settings.

#include "Barrel.h"
#include "Math/UnrealMathUtility.h"

void UBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	UE_LOG(LogTemp, Warning, TEXT("Elevate: %f"), Elevation);

	SetRelativeRotation(FRotator(Elevation, 0, 0));
}
