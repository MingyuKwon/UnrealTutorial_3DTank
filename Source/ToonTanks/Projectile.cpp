// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	RootComponent = staticMesh;

	particleComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle Comp"));
	particleComp->SetupAttachment(RootComponent);
	

	projectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	projectileComp->MaxSpeed = 1300.f;
	projectileComp->InitialSpeed = 1300.f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	staticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	UGameplayStatics::PlaySoundAtLocation(this, LanchSound, GetActorLocation());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr)
	{
		Destroy();
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto MyDamageType = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
		UGameplayStatics::ApplyDamage(OtherActor,Damage, MyOwnerInstigator, this, MyDamageType);
		if (HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
	}

	Destroy();


}

