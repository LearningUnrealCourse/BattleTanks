// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Turret.h"
#include "Barrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"
#include "AimingComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = Cast<UTankMovementComponent>(GetComponentByClass(UTankMovementComponent::StaticClass()));

	AimingComponent = Cast<UAimingComponent>(GetComponentByClass(UAimingComponent::StaticClass()));

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATank::Fire);
}

void ATank::Fire() 
{
	double currentTimeInSeconds = FPlatformTime::Seconds();
	if (m_pBarrel != nullptr && ((currentTimeInSeconds - m_dLastFireTimeSeconds) > FireRateSeconds))
	{
		FVector socketLocation = m_pBarrel->GetSocketLocation(FName("Projectile"));
		FRotator socketRotation = m_pBarrel->GetSocketRotation(FName("Projectile"));
		AProjectile* spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile, 
			socketLocation, 
			socketRotation
		);
		spawnedProjectile->Launch(LaunchSpeed);
		m_dLastFireTimeSeconds = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector HitLocation) {
	if (AimingComponent != nullptr)
	{
		AimingComponent->Aim(HitLocation, LaunchSpeed);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AimingComponent is missing!!!"))
	}
}

void ATank::SetBarrelReference(UBarrel * Barrel)
{
	m_pBarrel = Barrel;
}


