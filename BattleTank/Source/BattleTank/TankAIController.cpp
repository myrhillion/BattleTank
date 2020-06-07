// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

ATankAIController::ATankAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    auto ControlledTank = GetPawn();
    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    
    if (!ensure(PlayerTank && ControlledTank)) 
    {
        UE_LOG(LogTemp, Warning, TEXT("Assert failed on PlayerTank or ControlledTank in ATankAIController::Tick"));
        return; 
    }
    
    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centimeters
    UE_LOG(LogTemp, Warning, TEXT("Move to Actor called."));
    // aim towards player
    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    AimingComponent->Fire();
    
}

    
    
