// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
    float ClampedRelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1.0f, 1.0f);
    UE_LOG(LogTemp, Warning, TEXT("Made it to Barrel Elevate at speed %f"), ClampedRelativeSpeed);
    auto RotationChange = ClampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto Rotation = RelativeRotation.Yaw + RotationChange;

    SetRelativeRotation(FRotator(0, Rotation, 0));
}