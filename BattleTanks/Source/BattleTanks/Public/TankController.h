// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "TankController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankController : public AController
{
	GENERATED_BODY()

public:
	ATank* GetControlledTank() const;
};
