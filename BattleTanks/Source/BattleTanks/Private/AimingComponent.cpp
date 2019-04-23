// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.h"
#include "Turret.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UAimingComponent::SetBarrel(UBarrel * Barrel)
{
	this->Barrel = Barrel;
}

void UAimingComponent::SetTurret(UTurret * Turret)
{
	this->Turret = Turret;
}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAimingComponent::Aim(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel)
	{
		return;
	}

	FVector OutLaunchVelocity;
	// We are going to use a socket already placed in the end of the barrel
	FVector StartProjectileLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool solution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartProjectileLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (solution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
}

FRotator UAimingComponent::GetDeltaRotator(FRotator Rotator, FVector Direction) {
	FRotator AimAsRotator = Direction.Rotation();
	return AimAsRotator - Rotator;
}

void UAimingComponent::MoveBarrelTowards(FVector Direction)
{
	auto Rotator = Barrel->GetForwardVector().Rotation();
	auto DeltaRotator = GetDeltaRotator(Rotator, Direction);
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UAimingComponent::MoveTurretTowards(FVector Direction)
{
	auto Rotator = Turret->GetForwardVector().Rotation();
	auto DeltaRotator = GetDeltaRotator(Rotator, Direction);
	Turret->Rotate(DeltaRotator.Yaw);
}

