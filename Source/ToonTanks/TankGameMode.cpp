// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "PlayerTank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayerController.h"


void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
	TargetTowers = GetTargetTowerCount();
	

	
}

int32 ATankGameMode::GetTargetTowerCount()
{
	TArray<AActor*> outArray;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), outArray);
	return outArray.Num();
}

void ATankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (playerController)
		{
			playerController->SetPlayerEnabledState(false);
		}

		GameOver(false);
		
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		TargetTowers--;
		 
		if (TargetTowers <= 0)
		{
			GameOver(true);
		}
	}
}

void ATankGameMode::HandleGameStart()
{
	Tank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	playerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();


	if (playerController)
	{
		playerController->SetPlayerEnabledState(false);

		FTimerHandle playerTimerHandle;
		FTimerDelegate timerDelegate = FTimerDelegate::CreateUObject(
			playerController,
			&ATankPlayerController::SetPlayerEnabledState,
			true
		);

		GetWorldTimerManager().SetTimer(playerTimerHandle,
			timerDelegate,
			StartDelay,
			false
			);
	}
}

