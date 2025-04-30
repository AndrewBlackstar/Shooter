// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_Weapon.h"

// Sets default values
AS_Weapon::AS_Weapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Damage = 20.0f; // Default damage value

}

// Called when the game starts or when spawned
void AS_Weapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AS_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AS_Weapon::StartAction()
{
	BP_startAction();
}

void AS_Weapon::StopAction()
{
	BP_stopAction();
}

