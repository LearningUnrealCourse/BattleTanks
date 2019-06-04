// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Components/StaticMeshComponent.h"
#include "Barrel.h"
#include "Turret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	m_eCurrentState = EAimingState::Reloading;
	// ...
	
}

void UAimingComponent::Initialise(UBarrel* Barrel, UTurret* Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
}

// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_fLastFireTimeSeconds < FireRateSeconds)
	{
		m_fLastFireTimeSeconds += DeltaTime;
		m_eCurrentState = EAimingState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		m_eCurrentState = EAimingState::Aiming;
	}
	else
	{
		m_eCurrentState = EAimingState::Locked;
	}
}

bool UAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
	{
		return false;
	}
	return !Barrel->GetForwardVector().Equals(m_vAimDirection, 0.05);
}

void UAimingComponent::Aim(FVector HitLocation)
{
	if (!ensure(Barrel))
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
		m_vAimDirection = OutLaunchVelocity.GetSafeNormal();
		if (Barrel != nullptr && Turret != nullptr)
		{
			MoveBarrelTowards(m_vAimDirection);
			MoveTurretTowards(m_vAimDirection);
		}
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

void UAimingComponent::Fire()
{
	double currentTimeInSeconds = FPlatformTime::Seconds();
	if (Barrel != nullptr && m_eCurrentState == EAimingState::Locked)
	{
		FVector socketLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FRotator socketRotation = Barrel->GetSocketRotation(FName("Projectile"));

		AProjectile* spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile,
			socketLocation,
			socketRotation
			);
		spawnedProjectile->Launch(LaunchSpeed);

		m_fLastFireTimeSeconds = 0.f;
	}
}
