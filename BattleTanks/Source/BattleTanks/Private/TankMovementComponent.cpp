// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Track.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (Throw != 0.f) UE_LOG(LogTemp, Warning, TEXT("Throw: %f"), Throw)

	SetTrackThrottle(m_pRightTrack, Throw);
	SetTrackThrottle(m_pLeftTrack, Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	SetTrackThrottle(m_pRightTrack, -Throw);
	SetTrackThrottle(m_pLeftTrack, Throw);
}

void UTankMovementComponent::SetTrackThrottle(UTrack* Track, float Throw)
{
	if (Track != nullptr)
	{
		Track->SetThrottle(Throw);
	}
}

void UTankMovementComponent::Initialise(UTrack* RightTrack, UTrack* LeftTrack)
{
	if (RightTrack != nullptr)
	{
		m_pRightTrack = RightTrack;
	}

	if (LeftTrack != nullptr)
	{
		m_pLeftTrack = LeftTrack;
	}
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector currentForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector forwardIntention = MoveVelocity.GetSafeNormal(); //Unit direction
	float dotProduct = FVector::DotProduct(currentForward, forwardIntention);
	FVector crossProduct = FVector::CrossProduct(currentForward, forwardIntention);
	IntendMoveForward(dotProduct);
	IntendTurnRight(crossProduct.Z);
}