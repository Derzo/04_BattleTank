// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possessing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player pawn is %s"), *ControlledTank->GetName());
	}

}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank())	{	return;	}

	FVector HitLocation; // Out Parameter
	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect", is going to line trace
	{
		//UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *HitLocation.ToString());
		// TODO Tell controlled tank to aim at this point
	}

}

// Get world location if line trace through crosshair
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	UE_LOG(LogTemp, Warning, TEXT("Screen location: %s"), *ScreenLocation.ToString());
	// Deproject the screen position of the crosshair to a world direction
	// Line trace along that look direction and see what we hit (up to max range)
	HitLocation = FVector(1.0, 5.0, 100.0);

	return true;
}
