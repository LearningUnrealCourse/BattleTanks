// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
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
