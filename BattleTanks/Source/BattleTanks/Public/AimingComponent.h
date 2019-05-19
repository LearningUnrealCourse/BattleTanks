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

UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void Aim(FVector HitLocation, float LaunchSpeed);

	UFUNCTION(BlueprintCallable, Category = "SetUp")
	void Initialise(UBarrel* Barrel, UTurret* Turret);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimingState m_eCurrentState;

private:

	// Sets default values for this component's properties
	UAimingComponent();

	FRotator GetDeltaRotator(FRotator Rotator, FVector Direction);
	void MoveBarrelTowards(FVector direction);
	void MoveTurretTowards(FVector direction);

private:

	UBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;
	
};
