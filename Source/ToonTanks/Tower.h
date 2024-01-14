// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ATank
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;
	void HandleDestruction();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	class APlayerTank* Tank;

	UPROPERTY(EditDefaultsOnly)
	float FireRange = 500;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool inFIreRange();
};
