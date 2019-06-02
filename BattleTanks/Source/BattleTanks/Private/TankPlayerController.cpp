// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/Engine.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "DrawDebugHelpers.h"
#include "Tank.h"
#include "AimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Getting Pixel Coords at start since the value is not going to change 
	//*Have in mind if the screen is scalated this is not going to work
	CrosshHairScreenLocationPixelCoords = GetCrossHairScreenLocationInPixelCoordinates();

	auto aimingComponent = Cast<UAimingComponent>(GetControlledTank()->GetComponentByClass(UAimingComponent::StaticClass()));
	if (aimingComponent != nullptr)
	{
		AimingComponentFound(aimingComponent);
	}
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

//Find crosshair screen location (using viewport) in pixel coordinates
FVector2D ATankPlayerController::GetCrossHairScreenLocationInPixelCoordinates() {
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	return FVector2D(ViewportSizeX*CrossHairLocationX, ViewportSizeY*CrossHairLocationY);
}

void ATankPlayerController::GetViewportSize(int32& OutViewportSizeX, int32& OutViewportSizeY)
{
	FIntPoint ViewportSizeXY = GEngine->GameViewport->Viewport->GetSizeXY();
	OutViewportSizeX = ViewportSizeXY.X;
	OutViewportSizeY = ViewportSizeXY.Y;
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

void ATankPlayerController::AimAtCrosshair()
{
	auto Tank = GetControlledTank();
	if (Tank == nullptr)
	{
		return;
	}

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		Tank->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation)
{
	FVector CrossHairDirection;
	if (GetCrossHairScreenDirection(CrossHairDirection))
	{
		return GetCrossHairHitLocation(CrossHairDirection, OutHitLocation);
	}
	return false;
}

bool ATankPlayerController::GetCrossHairScreenDirection(FVector& OutCrossHairDirection)
{
	FVector WorldLocation; //This will have the camera World Location
	return DeprojectScreenPositionToWorld(
		CrosshHairScreenLocationPixelCoords.X,
		CrosshHairScreenLocationPixelCoords.Y,
		WorldLocation,
		OutCrossHairDirection);
}

bool ATankPlayerController::GetCrossHairHitLocation(FVector CrossHairDirection, FVector &OutHitLocation)
{
	//LineTrace Through CrossHair Direction
	FHitResult Hit;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + CrossHairDirection * TankRange;
	DrawDebugLine(GetWorld(), Start, End, FColor(255, 0, 0));
	if (GetWorld()->LineTraceSingleByChannel(
		Hit, 
		Start, 
		End,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = Hit.Location;
		return true;
	}
	OutHitLocation = FVector(0.f);
	return false;
}


