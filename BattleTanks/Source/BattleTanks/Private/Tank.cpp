// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Turret.h"
#include "Barrel.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Aiming component is a requirement, that is way we instantiate it at creation time
	AimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));
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

void ATank::Fire() {
	UE_LOG(LogTemp, Warning, TEXT("Firing to aimed position"))
}

void ATank::AimAt(FVector HitLocation) {
	AimingComponent->Aim(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UBarrel * Barrel)
{
	AimingComponent->SetBarrel(Barrel);
}

void ATank::SetTurretReference(UTurret * Turret)
{
	AimingComponent->SetTurret(Turret);
}


