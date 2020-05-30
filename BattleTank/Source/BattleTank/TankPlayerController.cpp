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
    
    AimTowardsCrossHair();
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
        // UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *HitLocation.ToString());
        // TODO Tell controlled tank to aim at this point
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;

    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    // UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
    }
    // deproject screen position of the cursor to a world direction
    // line trace along that LookDirection, see what we hit up to a max range

    // HitLocation = FVector(1.0);
    return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
    FVector CameraWorldLocation;
    FVector WorldDirection;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X, 
        ScreenLocation.Y, 
        CameraWorldLocation, 
        LookDirection);
    
}