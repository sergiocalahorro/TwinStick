// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/GameplayStatics.h"
#include "../Components/HealthComponent.h"
#include "../Projectiles/BaseProjectile.h"
#include "../ObjectPool/ObjectPoolComponent.h"

// Sets default values for this pawn's properties
ABasePawn::ABasePawn()
{
	// Mesh setup
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = StaticMesh;

	// Camera setup
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true);
	CameraBoom->bDoCollisionTest = false;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);
	CameraComponent->bUsePawnControlRotation = false;

	// Shooting
	ShootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ShootPoint"));
	ShootPoint->SetupAttachment(RootComponent);

	ObjectPoolComponent = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPoolComponent"));
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// Rotate towards movement direction
	UpdatePawnRotation(DeltaSeconds);

	// Fire shot
	if (bCanFire)
	{
		const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
		FireShot(FireDirection);
	}
}

/*
 * Setup player inputs
 * @param PlayerInputComponent - Player's input component
 */ 
void ABasePawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	// Setup bindings
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABasePawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABasePawn::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("ShootForward"), this, &ABasePawn::FireForward);
	PlayerInputComponent->BindAxis(TEXT("ShootRight"), this, &ABasePawn::FireRight);
}

/*
 * Move forward input
 * @param AxisValue - Forward input value
 */
void ABasePawn::MoveForward(float AxisValue)
{
	// Store axis value
	MoveForwardValue = AxisValue;

	// Calculate movement direction
	const FVector MovementDirection = FVector(AxisValue, 0.f, 0.f);
	const FVector Movement = MovementDirection * MovementSpeed * GetWorld()->GetDeltaSeconds();
	AddActorWorldOffset(Movement, true);
}

/*
 * Move right input
 * @param AxisValue - Right input value
 */
void ABasePawn::MoveRight(float AxisValue)
{
	// Store axis value
	MoveRightValue = AxisValue;

	// Calculate movement direction
	const FVector MovementDirection = FVector(0.f, AxisValue, 0.f);
	const FVector Movement = MovementDirection * MovementSpeed * GetWorld()->GetDeltaSeconds();
	AddActorWorldOffset(Movement, true);
}

/*
 * Fire forward input
 * @param AxisValue - Forward input value
 */
void ABasePawn::FireForward(float AxisValue)
{
	// Store axis value
	FireForwardValue = AxisValue;
}

/*
 * Fire right input
 * @param AxisValue - Right input value
 */
void ABasePawn::FireRight(float AxisValue)
{
	// Store axis value
	FireRightValue = AxisValue;
}

/*
 * Update pawn rotation based on movement inputs
 * @param DeltaSeconds - Elapsed seconds each frame
 */
void ABasePawn::UpdatePawnRotation(float DeltaSeconds)
{
	const FVector MovementDirection = FVector(MoveForwardValue, MoveRightValue, 0.f).GetClampedToMaxSize(1.0f);
	if (MovementDirection.SizeSquared() > 0.f)
	{
		const FRotator MovementRotation = (MovementDirection * MovementSpeed * DeltaSeconds).Rotation();
		SetActorRotation(MovementRotation);
	}
}

/*
 * Shoot in the direction given by fire inputs
 * @param FireDirection - Shot direction
 */
void ABasePawn::FireShot(FVector FireDirection)
{
	// If fire stick is pushed in any direction
	if (FireDirection.SizeSquared() > FireInputThreshold)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		const FVector ProjectileLocation = GetActorLocation() + FireRotation.RotateVector(ShootPoint->GetRelativeLocation());

		// ToDo: Object Pooling
		ABaseProjectile* Projectile = Cast<ABaseProjectile>(ObjectPoolComponent->GetPoolableObject());
		if (Projectile)
		{
			Projectile->SetOwner(this);
			Projectile->SetActorLocation(ProjectileLocation);
			Projectile->SetActorRotation(FireRotation);
			Projectile->SetLifeSpan(ProjectileLifeSpan);
			Projectile->Activate();
		}

		//FActorSpawnParameters SpawnParameters;
		//SpawnParameters.Owner = this;

		//ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, ProjectileLocation, FireRotation, SpawnParameters);

		// Allow shooting again after some delay
		bCanFire = false;
		FTimerHandle ShotTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, FTimerDelegate::CreateLambda([&] { bCanFire = true; }), FireRate, false);
	}
}

/*
 * Function called when pawn is destroyed
 */
void ABasePawn::HandleDestruction()
{

}