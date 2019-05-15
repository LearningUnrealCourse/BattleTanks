// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Turret.h"
#include "Barrel.h"
#include "Projectile.h"
#include "TankMovementComponent.h"

// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Aiming component is a requirement, that is way we instantiate it at creation time
	AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));

	MovementComponent = Cast<UTankMovementComponent>(GetComponentByClass(UTankMovementComponent::StaticClass()));
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
		UE_LOG(LogTemp, Warning, TEXT("Firing to aimed position"));
		FVector socketLocation = m_pBarrel->GetSocketLocation(FName("Projectile"));
		FRotator socketRotation = m_pBarrel->GetSocketRotation(FName("Projectile"));
		UE_LOG(LogTemp, Warning, TEXT("Socket Location: %s"), *socketLocation.ToString());
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
	AimingComponent->Aim(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UBarrel * Barrel)
{
	AimingComponent->SetBarrel(Barrel);
	m_pBarrel = Barrel;
}

void ATank::SetTurretReference(UTurret * Turret)
{
	AimingComponent->SetTurret(Turret);
}


