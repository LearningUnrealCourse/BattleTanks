// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankController.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void AimingComponentFound(UAimingComponent* AimingComponentRef);

private:

	UPROPERTY(EditAnywhere)
	float CrossHairLocationX = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrossHairLocationY = 0.33333;

	UPROPERTY(EditAnywhere)
	float TankRange = 25000.0f;

	FVector2D CrosshHairScreenLocationPixelCoords;

	void AimAtCrosshair();
	bool GetSightRayHitLocation(FVector & OutHitLocation);
	bool GetCrossHairHitLocation(FVector CrossHairDirection, FVector & OutHitLocation);
	bool GetCrossHairScreenDirection(FVector & OutCrossHairScreenDirection);
	FVector2D GetCrossHairScreenLocationInPixelCoordinates();
	void GetViewportSize(int32 & OutViewportSizeX, int32 & OutViewportSizeY);

};
