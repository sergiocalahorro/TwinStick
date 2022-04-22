// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values for this actor's properties
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->OnComponentHit.AddDynamic(this, &ABaseProjectile::OnHit);
	RootComponent = StaticMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/**
 * Activate projectile
 */
void ABaseProjectile::Activate()
{
	Super::Activate();
	ProjectileMovementComponent->Activate();
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed;
}

/**
 * Deactivate projectile
 */
void ABaseProjectile::Deactivate()
{
	Super::Deactivate();
	ProjectileMovementComponent->Deactivate();
	ProjectileMovementComponent->Velocity = FVector::ZeroVector;
}

/**
 * Function called whenever this Actor collides with another Actor
 * @param	HitComponent - Actor's component that hit with OtherActor
 * @param	OtherActor - Actor that collided with this Actor
 * @param	OtherComponent - OtherActor's component that hit with this Actor
 * @param	NormalImpulse - Hit's normal
 * @param	Hit - Hit's information
 */
void ABaseProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("ABaseProjectile::OnHit - HIT!"));

	if (OtherActor == GetOwner())
	{
		return; 
	}

	Deactivate();
}