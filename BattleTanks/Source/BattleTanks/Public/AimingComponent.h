// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AimingComponent.generated.h"

//Forward Declaration
class UBarrel; 
class UTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Aim(FVector HitLocation, float LaunchSpeed);


	void SetBarrel(UBarrel* Barrel);
	void SetTurret(UTurret* Barrel);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UBarrel* Barrel = nullptr;
	UTurret* Turret = nullptr;

	// Sets default values for this component's properties
	UAimingComponent();

	FRotator GetDeltaRotator(FRotator Rotator, FVector Direction);
	void MoveBarrelTowards(FVector direction);
	void MoveTurretTowards(FVector direction);
		
};
