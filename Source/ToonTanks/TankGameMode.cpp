// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "PlayerTank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "TankPlayerController.h"


void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
	playerController = Cast<ATankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
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
		
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

