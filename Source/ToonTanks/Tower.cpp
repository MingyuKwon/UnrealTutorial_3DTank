// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "PlayerTank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (inFIreRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}

}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (inFIreRange())
	{
		Fire();
	}
}

bool ATower::inFIreRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}