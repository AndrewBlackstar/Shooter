// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/S_Item.h"
#include "S_DoorKey.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AS_DoorKey : public AS_Item
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Key")
	UStaticMeshComponent* KeyMesh;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Key")
	FName KeyName;

public:

	// Sets default values for this actor's properties
	AS_DoorKey();
public:

	UFUNCTION(BlueprintCallable, Category = "Key")
	FName GetKeyName() const { return KeyName; }

protected:

	virtual void PickUp(AS_Character01* PlayerActor) override;
};
