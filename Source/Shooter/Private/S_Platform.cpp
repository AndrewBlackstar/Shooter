// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Platform.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
AS_Platform::AS_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootComponent"));
	RootComponent = CustomRootComponent;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	PlatformMesh->SetupAttachment(CustomRootComponent);

	bIsGoingUp = true;
	MinDistance = 0.0f;
	MaxDistance = 50.0f;
	PlatformSpeed = 10.0f;

}

// Called when the game starts or when spawned
void AS_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AS_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform();
}

void AS_Platform::MovePlatform()
{
	FVector UpDirection = UKismetMathLibrary::GetUpVector(GetActorRotation());

	if (bIsGoingUp) 
	{
		UpDirection = UpDirection;
	}
	else
	{
		UpDirection = UpDirection *-1;
	}

	FVector CurrentVelocity = UpDirection * PlatformSpeed;
	FVector newPosition = GetActorLocation() + CurrentVelocity;

	SetActorLocation(newPosition);

	if (bIsGoingUp && GetActorLocation().Z >= MaxDistance) {
		bIsGoingUp = false;
	}
	else if (!bIsGoingUp && GetActorLocation().Z <= MinDistance)
	{
		bIsGoingUp = true;
	}
}
