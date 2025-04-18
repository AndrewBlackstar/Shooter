// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Door.h"

// Sets default values
AS_Door::AS_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("CustomRootComponent"));
	RootComponent = CustomRootComponent;

	DoorFrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameMesh"));
	DoorFrameMesh->SetupAttachment(CustomRootComponent);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(CustomRootComponent);

	DoorOpenAngle = -90.0f;

}

// Called when the game starts or when spawned
void AS_Door::BeginPlay()
{
	Super::BeginPlay();
	OpenDoor();
}

// Called every frame
void AS_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_Door::OpenDoor()
{
	FRotator NewRotation = FRotator(0.0f, DoorOpenAngle, 0.0f);
	DoorMesh->SetRelativeRotation(NewRotation);
}

