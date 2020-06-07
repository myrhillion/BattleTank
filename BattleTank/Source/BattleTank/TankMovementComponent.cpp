// Copyright Douglas Taggart as part of Unreal C++ Course on GameDev.TV

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing Left or Right Track references in UTankMovementComponent::Initialise"));
		return; 
	}
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;

}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	// UE_LOG(LogTemp, Warning, TEXT("Intend move forward throw: %f"), Throw);
	if (!ensure(LeftTrack && RightTrack)) 
	{ 
		UE_LOG(LogTemp, Warning, TEXT("Missing Left or Right Track references in UTankMovementComponent::IntendMoveForward"));
		return; 
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
	
	// TODO prevent double speed due to dual control use

}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call super as we're replacing functionality here
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto MoveThrow = FVector::DotProduct(AIForwardIntention, TankForward);
	auto RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	
	IntendTurnRight(RightThrow);
	IntendMoveForward(MoveThrow);
	// UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	// UE_LOG(LogTemp, Warning, TEXT("Intend Turn Right throw: %f"), Throw);
	if (!ensure(LeftTrack && RightTrack)) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Missing Left or Right Track references in UTankMovementComponent::IntendTurnRight"));
		return; 
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}