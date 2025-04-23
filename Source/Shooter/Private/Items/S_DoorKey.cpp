// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/S_DoorKey.h"
#include "S_Character01.h"

AS_DoorKey::AS_DoorKey()
{
	KeyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyMesh"));
	KeyMesh->SetupAttachment(RootComponent);
	KeyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	KeyName = "KeyA";
}

void AS_DoorKey::PickUp(AS_Character01* PlayerActor)
{
	Super::PickUp(PlayerActor);
	PlayerActor->AddKey(KeyName);
	Destroy();
}

