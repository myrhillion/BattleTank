// Copyright Douglas Taggart as part of Unreal C++ Course on GameDev.TV

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;  


	// ...
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	// So that first fire requires reload
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// UE_LOG(LogTemp, Warning, TEXT("AimComponent Ticking."));
	if ((GetWorld()->GetTimeSeconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

void UTankAimingComponent::Fire()
{
	//auto Time = GetWorld()->GetTimeSeconds();

	

	// bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;
	if (FiringState != EFiringState::Reloading)
	{
		// Spawn a projectile at the socket location on barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		// TODO fix firing
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		return;
	}
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	// if (!BarrelToSet || !TurretToSet) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return (!BarrelForward.Equals(AimDirection, 0.01f));
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
	{
		// UE_LOG(LogTemp, Warning, TEXT("In TankAimingComponent::AimAt, but no Barrel reference found"));
		return;
	}
	
	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace  // paramater must be present to solve, preventing bug
	);

	auto Time = GetWorld()->GetTimeSeconds();
	if(bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		
		// auto OurTankName = GetOwner()->GetName();
		// auto BarrelLocation = Barrel->GetComponentLocation().ToString();
		// UE_LOG(LogTemp, Warning, TEXT("%f: %s aiming at: %s"), Time, *TankName, *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}
	else
	{
		// UE_LOG(LogTemp, Warning, TEXT("%f: No aim solve found"), Time);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	// rotate turret and elevate barrel, x, y, z towards the StartLocation the barrel needs to have to accomodate firing solut
	// Work out difference between current barrel rotation and aim direction.

	if (!ensure(Barrel) || !ensure(Turret)) { return; }

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	// UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());

	Barrel->Elevate(DeltaRotator.Pitch);

	// Always yaw the shortest of left right 180
	if (FMath::Abs(DeltaRotator.Yaw) < 180.0f)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}
