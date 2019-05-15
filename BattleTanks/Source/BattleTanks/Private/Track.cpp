// Fill out your copyright notice in the Description page of Project Settings.

#include "Track.h"

void UTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("SetThrottle called: %f"), Throttle)
	FVector forceToApply = GetForwardVector() * Throttle * DrivingForce;
	FVector forceLocation = GetComponentLocation();
	UPrimitiveComponent* tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceToApply, forceLocation);
}