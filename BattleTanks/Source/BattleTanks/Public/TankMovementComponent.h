// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTrack;

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = SetUp)
		void SetRightTrack(UTrack* Track);

	UFUNCTION(BlueprintCallable, Category = SetUp)
		void SetLeftTrack(UTrack* Track);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Throw);

private:

	void SetTrackThrottle(UTrack* Track, float Throw);

private:

	UTrack* m_pRightTrack = nullptr;

	UTrack* m_pLeftTrack = nullptr;
};
