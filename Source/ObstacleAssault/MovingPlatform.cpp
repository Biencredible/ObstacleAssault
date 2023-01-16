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
	if(shouldPlatformReturn())
	{
		FVector moveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + moveDirection * moveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector currentLocation = GetActorLocation();
		currentLocation = currentLocation + PlatformVelocity * DeltaTime;
		SetActorLocation(currentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FString name = GetName();
	UE_LOG(LogTemp, Display, TEXT("Rotation of %s"), *name);	
}

bool AMovingPlatform::shouldPlatformReturn() const
{
	return getDistanceMoved() > moveDistance;
}

float AMovingPlatform::getDistanceMoved() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

