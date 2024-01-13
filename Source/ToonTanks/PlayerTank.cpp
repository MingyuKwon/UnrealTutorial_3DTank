// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerTank::APlayerTank()
{
	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	springArmComp->SetupAttachment(RootComponent);

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComp->SetupAttachment(springArmComp);
}

void APlayerTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerTank::Move);
}

void APlayerTank::Move(float value)
{
	FVector moveVector(1.0f, 0.0f, 0.0f);
	moveVector = moveVector * value * speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(moveVector);
}