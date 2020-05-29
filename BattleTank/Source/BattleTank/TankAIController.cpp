// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

ATank* ATankAIController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("TankAIController Begin Play"));

    GetPlayerTank();

    auto PlayerTank = GetPlayerTank();
    if (PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s referenced by AI pawn/tank."), *PlayerTank->GetName());
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("No Player Tank available."));
    }
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if (PlayerPawn)
    {
        return Cast<ATank>(PlayerPawn);
    }
    else
    {
        return nullptr;
    }

}
    
    
