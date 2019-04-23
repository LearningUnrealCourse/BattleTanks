// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AimingComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UBarrel; //Forward Declaration
class UTurret; //Forward Declaration

UCLASS()
class BATTLETANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UBarrel* Barrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTurret* Turret);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UAimingComponent* AimingComponent = nullptr;

private:

	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 100000; // TODO find sensible default

};
