// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

//Aiming States
UENUM()
enum class EAimingState : uint8
{
	Locked,
	Aiming,
	Reloading
};

class UBarrel; 
class UTurret;
class AProjectile;

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Aim(FVector HitLocation);

	void Fire();

	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void Initialise(UBarrel* Barrel, UTurret* Turret);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimingState m_eCurrentState = EAimingState::Reloading;

private:

	// Sets default values for this component's properties
	UAimingComponent();

	bool IsBarrelMoving();

	FRotator GetDeltaRotator(FRotator Rotator, FVector Direction);
	void MoveBarrelTowards(FVector direction);
	void MoveTurretTowards(FVector direction);

private:

	UPROPERTY(EditAnywhere, Category = "Firing")
	float LaunchSpeed = 4000.f;

	UPROPERTY(EditAnywhere, Category = "Firing")
	float FireRateSeconds = 2.f;

	UPROPERTY(EditAnywhere, Category = "SetUp")
	TSubclassOf<AProjectile> Projectile;

	UBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;

	float m_fLastFireTimeSeconds = 0;

	FVector m_vAimDirection;
	
};
