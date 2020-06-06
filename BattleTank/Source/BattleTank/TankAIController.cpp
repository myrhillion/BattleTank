// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

ATankAIController::ATankAIController()
{
    PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    // AimTowardsCrossHair();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    auto ControlledTank = GetPawn();

    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!ensure(PlayerTank && ControlledTank)) { return; }
    
    // move towards player
    MoveToActor(PlayerTank, AcceptanceRadius); // TODO check radius is in centimeters
    UE_LOG(LogTemp, Warning, TEXT("Move to Actor called."));
    // aim towards player
    AimingComponent->AimAt(PlayerTank->GetActorLocation());
    AimingComponent->Fire();
    
}

    
    
