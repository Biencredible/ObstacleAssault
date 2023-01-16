// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Move Platform forwards
		// get current location
	FVector currentLocation = GetActorLocation();
		// add vector to that location
	currentLocation = currentLocation + PlatformVelocity * DeltaTime;
		// set the location
	SetActorLocation(currentLocation);
	// Send platform back if gone too far
		// Check how far we've moved
	float distanceMoved = FVector::Dist(StartLocation, currentLocation);
		// Reverse direction of motion if gone too far
	if(distanceMoved > moveDistance)
	{
		FString name = GetName();
		float overShoot = distanceMoved - moveDistance;
		UE_LOG(LogTemp, Display, TEXT("Overshoot Distance of %s: %f"), *name, overShoot);
		FVector moveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + moveDirection * moveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FString name = GetName();
	UE_LOG(LogTemp, Display, TEXT("Rotation of %s"), *name);	
}

