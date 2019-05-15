// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Track.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
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

void UTankMovementComponent::SetRightTrack(UTrack* Track)
{
	if (Track != nullptr)
	{
		m_pRightTrack = Track;
	}
}

void UTankMovementComponent::SetLeftTrack(UTrack* Track)
{
	if (Track != nullptr)
	{
		m_pLeftTrack = Track;
	}
}