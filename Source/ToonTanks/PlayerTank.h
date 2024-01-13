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

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private :
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* springArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* cameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements", meta = (AllowPrivateAccess = "true"))
	float Speed = 200;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movements", meta = (AllowPrivateAccess = "true"))
	float RotateSpeed = 70;

	void Move(float value);
	void Turn(float value);

};
