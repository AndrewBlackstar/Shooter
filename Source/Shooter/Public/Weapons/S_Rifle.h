// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/S_Weapon.h"
#include "S_Rifle.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AS_Rifle : public AS_Weapon
{
	GENERATED_BODY()

public:
	AS_Rifle();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace|Debug")
	bool bDrawDebugLine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "LineTrace")
	float TraceLength;

protected:

	virtual void StartAction() override;
	virtual void StopAction() override;

};
