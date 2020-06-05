// Copyright Douglas Taggart as part of Unreal C++ Course on GameDev.TV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent* TankMovementComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000;  //  1000m/second

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// local barrel reference for spawning projectiles
	UTankBarrel* Barrel = nullptr; // TODO remove

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
};
