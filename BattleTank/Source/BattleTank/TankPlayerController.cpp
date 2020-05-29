// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"



void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play"));

    AActor* OurTank = GetControlledTank();
    if (OurTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s pawn captured."), *OurTank->GetName());
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("No Controlled Tank available."));
    }
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // AimTowardsCrossHair();
    // UE_LOG(LogTemp, Warning, TEXT("Ticking in TankPlayerController"));
}

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrossHair()
{
    if (!GetControlledTank()){return;}


    FVector HitLocation; // Out Parameter
    if (GetSightRayHitLocation(HitLocation)) // is going to ray-trace later
    {
        // Get World Location through crosshair (line trace)
        // If it hits the landscape
        // Tell controlled tank to aim at this point
        UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
        // TODO Tell controlled tank to aim at this point
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    HitLocation = FVector(1.0);
    return true;
}
