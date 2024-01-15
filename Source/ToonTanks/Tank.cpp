// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USphereComponent>(TEXT("Shooting Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ATank::HandleDestruction()
{
	// 죽을 때 방생하는 시작. 음향 효과 
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
}

void ATank::RotateTurret(FVector targetPoint)
{
	FVector ToTarget = targetPoint - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw,0.f);

	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(), 
		LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		10.f));
}

void ATank::Fire()
{
	auto projectile = GetWorld()->SpawnActor<AProjectile>
		(ProjectileClass, 
		ProjectileSpawnPoint->GetComponentLocation(), 
		ProjectileSpawnPoint -> GetComponentRotation());

	projectile->SetOwner(this);
}


