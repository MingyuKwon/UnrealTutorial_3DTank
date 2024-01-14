// Fill out your copyright notice in the Description page of Project Settings.


#include "TankGameMode.h"
#include "PlayerTank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void ATankGameMode::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<APlayerTank>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void ATankGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (Tank->GetPlayerController())
		{
			Tank->DisableInput(Tank->GetPlayerController());
			Tank->GetPlayerController()->bShowMouseCursor = false;
		}
		
	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
	}
}

