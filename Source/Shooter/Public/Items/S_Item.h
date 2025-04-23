// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Item.generated.h"


class USphereComponent;
class AS_Character01;

UCLASS()
class SHOOTER_API AS_Item : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* MainCollision;
	
public:	
	// Sets default values for this actor's properties
	AS_Item();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PickUp(AS_Character01 * PlayerActor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Item")
	void Bp_PickUp(AS_Character01* PlayerActor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
