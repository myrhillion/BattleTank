// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
    Super::SetPawn(InPawn);
    if (InPawn)
    {
        auto PossessedTank = Cast<ATank>(InPawn);
        if (!ensure(PossessedTank)) { return; }
        // TODO Subscribe our local method to tank's death event
        PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
    }
}

void ATankAIController::OnPossessedTankDeath()
{
    if (!GetPawn()) { return; }
    GetPawn()->DetachFromControllerPendingDestroy();
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

    // if aiming or locked, then fire
    if (AimingComponent->GetFiringState() == EFiringState::Locked)
    {
        AimingComponent->Fire();
    }
    
    
}

    
    
