// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	return Cast<ATank>(PlayerPawn); //if cannot find PlayerController will return nullptr
}

void ATankAIController::Tick(float DeltaTime)
{
	ATank* playerTank = GetPlayerTank();
	if (playerTank)
	{
		EPathFollowingRequestResult::Type result = MoveToActor(playerTank, AcceptanceRadius);
		if (result == EPathFollowingRequestResult::Type::AlreadyAtGoal)
		{
			GetControlledTank()->AimAt(playerTank->GetActorLocation());
			GetControlledTank()->Fire();
		}
	}
}
