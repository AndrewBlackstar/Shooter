// Fill out your copyright notice in the Description page of Project Settings.


#include "S_Door.h"
#include "Components/BoxComponent.h"
#include "S_Character01.h"

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

	DoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
	DoorCollision->SetupAttachment(CustomRootComponent);
	DoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DoorCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	DoorCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	DoorOpenAngle = -90.0f;
	DoorKeyName = "KeyA";
}

// Called when the game starts or when spawned
void AS_Door::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AS_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DoorCollision->OnComponentBeginOverlap.AddDynamic(this, &AS_Door::CheckForPlayerOverlap);
}

void AS_Door::OpenDoor()
{
	/*FRotator NewRotation = FRotator(0.0f, DoorOpenAngle, 0.0f);
	DoorMesh->SetRelativeRotation(NewRotation);*/

	bIsDoorOpen = true;
	Bp_OpenDoor();
}

void AS_Door::CheckForPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsDoorOpen)
	{
		return;
	}

	if (IsValid(OtherActor))
	{
		AS_Character01* PlayerCharacter = Cast<AS_Character01>(OtherActor);
		if (IsValid(PlayerCharacter))
		{
			if (PlayerCharacter->HasKey(DoorKeyName))
			{
				OpenDoor();
			}

		}
	}
	
}

