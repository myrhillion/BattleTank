// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();

private:
	//ATank* ControlledTank = nullptr;
	//ATank* PlayerTank = nullptr;

	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	// How close AI Tank can get to player
	float AcceptanceRadius = 3000;
};
