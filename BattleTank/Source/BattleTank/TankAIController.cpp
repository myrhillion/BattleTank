// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"

ATankAIController::ATankAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    //ControlledTank = Cast<ATank>(GetPawn());
    //PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    /*if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Player Tank available."));
        return;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("%s referenced by AI pawn/tank."), *PlayerTank->GetName());
    }

    if (!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Assigning Controlled Tank Failed."));
        return;
    }

    if (!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("Assigning PlayerTank Failed."));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));*/
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // AimTowardsCrossHair();

    auto ControlledTank = Cast<ATank>(GetPawn());

    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    if (ensure(PlayerTank))
    {
        // move towards player
        MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centimeters
        // aim towards player
        ControlledTank->AimAt(PlayerTank->GetActorLocation());
        // fire if ready
        ControlledTank->Fire();
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("In Tick: No PlayerTank reference available."));
    }
}

    
    
