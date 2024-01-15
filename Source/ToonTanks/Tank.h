// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void HandleDestruction();

protected:
	void RotateTurret(FVector targetPoint);
	void Fire();

private:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite , Category = "Compoents", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Compoents", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* ProjectileSpawnPoint;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Compoents", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Compoents", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* DeathSound;
};
