// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "S_Platform.generated.h"

UCLASS()
class SHOOTER_API AS_Platform : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USceneComponent* CustomRootComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PlatformMesh;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	bool bIsGoingUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float PlatformSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float MinDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Platform")
	float MaxDistance;

public:	
	// Sets default values for this actor's properties
	AS_Platform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Platform")
	void MovePlatform();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



};
