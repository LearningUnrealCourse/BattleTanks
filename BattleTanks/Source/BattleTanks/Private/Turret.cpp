// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Math/UnrealMathUtility.h"

void UTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Yaw + RotationChange;
	UE_LOG(LogTemp, Warning, TEXT("Rotate: %f"), RawNewRotation);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));
}
