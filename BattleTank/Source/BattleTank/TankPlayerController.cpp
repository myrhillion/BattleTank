// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"



void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }
    FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    AimTowardsCrossHair();
}

void ATankPlayerController::AimTowardsCrossHair()
{
    if (!GetPawn()) { return; } // e.g. if not possessing
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)){return;}

    FVector HitLocation; // Out Parameter
    if (GetSightRayHitLocation(HitLocation)) // is going to ray-trace later
    {
        AimingComponent->AimAt(HitLocation);
    }
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }
        // TODO Subscribe our local method to tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnPossessedTankDeath);
    }
}

void ATankPlayerController::OnPossessedTankDeath()
{
    StartSpectatingOnly();
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;

    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
    // UE_LOG(LogTemp, Warning, TEXT("Screen Location: %s"), *ScreenLocation.ToString());

    // FHitResult OutHitLocation;
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation, LookDirection))
    {
        // line trace along that LookDirection, see what we hit up to a max range
        
        // UE_LOG(LogTemp, Warning, TEXT("Look direction: %s"), *LookDirection.ToString());
        return GetLookVectorHitLocation(LookDirection, OutHitLocation);
    }
    return false;
    
    
    
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

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
    // LineTraceSingleByChannel, UWorld
    FHitResult HitResult;
    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
    if(GetWorld()->LineTraceSingleByChannel(
        HitResult,
        StartLocation,
        EndLocation,
        ECollisionChannel::ECC_Camera)
        )
    {
        // set hit location
        OutHitLocation = HitResult.Location; 
        return true;
    }
    else 
    {
        OutHitLocation = FVector(0);
        return false;
    }
}