// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;
/**
 * Controls AI Tank Movement
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();

protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 7000;

	UFUNCTION()
		void OnPossessedTankDeath();

private:
	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* InPawn) override;

	void Tick(float DeltaTime);

	// How close AI Tank can get to player
	

};
