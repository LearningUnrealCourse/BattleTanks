// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankPlayerController.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, Category = "Path Finding")
	float AcceptanceRadius = 3000.f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;
	ATank* GetPlayerTank() const;
};
