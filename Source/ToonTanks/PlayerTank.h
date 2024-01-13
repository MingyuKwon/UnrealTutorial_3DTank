// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "PlayerTank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API APlayerTank : public ATank
{
	GENERATED_BODY()

public :
	APlayerTank();

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* cameraComp;

};
