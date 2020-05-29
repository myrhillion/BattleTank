// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

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