// Copyright Douglas Taggart as part of Unreal C++ Course on GameDev.TV

#pragma once

#include "CoreMinimal.h"
#include "Tank.generated.h"

// Forward Declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	// returns current health as percentage of starting health, between 0 and 1.
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent() const;

	FTankDelegate OnDeath;

private:

	ATank();
	virtual void BeginPlay() override;

	// Sets default values for this pawn's properties
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth; //initialized in Begin Play
};
