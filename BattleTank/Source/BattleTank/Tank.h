// Copyright Douglas Taggart as part of Unreal C++ Course on GameDev.TV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declarations
class UTankBarrel;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

private:
	// Sets default values for this pawn's properties
	ATank();
	
	virtual void BeginPlay() override;

	// TODO Remove once firing is moved to aiming component
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 5000;  //  1000m/second

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	// local barrel reference for spawning projectiles
	UTankBarrel* Barrel = nullptr; // TODO remove

	float ReloadTimeInSeconds = 3;
	double LastFireTime = 0;
};
