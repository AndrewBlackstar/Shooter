// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/S_Item.h"
#include "Components/SphereComponent.h"
#include "S_Character01.h"

// Sets default values
AS_Item::AS_Item()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainCollision = CreateDefaultSubobject<USphereComponent>(TEXT("MainCollision"));
	MainCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MainCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	MainCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	MainCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	MainCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = MainCollision;


	
}

// Called when the game starts or when spawned
void AS_Item::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AS_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_Item::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	// Check if the overlapping actor is a player character

	if (IsValid(OtherActor))
	{
		AS_Character01* PlayerCharacter = Cast<AS_Character01>(OtherActor);
		if(IsValid(PlayerCharacter))
		{
			PickUp(PlayerCharacter);
		}
	}
	
}

void AS_Item::PickUp(AS_Character01* PlayerActor)
{
	Bp_PickUp(PlayerActor);
}


