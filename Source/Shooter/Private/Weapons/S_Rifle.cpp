// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/S_Rifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AS_Rifle::AS_Rifle()
{
	TraceLength = 10000.0f;
}

void AS_Rifle::StartAction()
{
	Super::StartAction();
	UE_LOG(LogTemp, Log, TEXT("Rifle started firing!"));

	AActor* CurrentOwner = GetOwner();

	if (IsValid(CurrentOwner))
	{
		FVector EyeLocation;
		FRotator EyeRotation;

		CurrentOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector ShotPoint = EyeRotation.Vector();
		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * TraceLength);

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(CurrentOwner);
		QueryParams.AddIgnoredActor(this);
		QueryParams.bTraceComplex = true;


		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, EyeLocation, TraceEnd, ECC_Visibility, QueryParams);

		if (bHit)
		{
			//Damage
			AActor* HitActor = HitResult.GetActor();
			if (IsValid(HitActor))
			{
				UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
				UGameplayStatics::ApplyPointDamage(HitActor, Damage, ShotPoint, HitResult, CurrentOwner->GetInstigatorController(), this, DamageType);
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("Hit Actor is not valid"));
			}
		}

		if (bDrawDebugLine)
		{
			DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
		}
	}

}


void AS_Rifle::StopAction()
{
	Super::StopAction();
	UE_LOG(LogTemp, Log, TEXT("Rifle stopped firing!"));
}
