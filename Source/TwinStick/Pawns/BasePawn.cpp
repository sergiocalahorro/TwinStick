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
#include "DrawDebugHelpers.h"

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
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

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

void ABasePawn::HandleDestruction()
{
	// ToDo: Particles, sounds, camera shake... on destruction
}

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

void ABasePawn::MoveForward(float AxisValue)
{
	// Store axis value
	MoveForwardValue = AxisValue;

	// Calculate movement direction
	const FVector MovementDirection = FVector(AxisValue, 0.f, 0.f);
	const FVector Movement = MovementDirection * MovementSpeed * GetWorld()->GetDeltaSeconds();
	AddActorWorldOffset(Movement, true);
}

void ABasePawn::MoveRight(float AxisValue)
{
	// Store axis value
	MoveRightValue = AxisValue;

	// Calculate movement direction
	const FVector MovementDirection = FVector(0.f, AxisValue, 0.f);
	const FVector Movement = MovementDirection * MovementSpeed * GetWorld()->GetDeltaSeconds();
	AddActorWorldOffset(Movement, true);
}

void ABasePawn::FireForward(float AxisValue)
{
	// Store axis value
	FireForwardValue = AxisValue;
}

void ABasePawn::FireRight(float AxisValue)
{
	// Store axis value
	FireRightValue = AxisValue;
}

void ABasePawn::UpdatePawnRotation(float DeltaSeconds)
{
	const FVector MovementDirection = FVector(MoveForwardValue, MoveRightValue, 0.f).GetClampedToMaxSize(1.0f);
	if (MovementDirection.SizeSquared() > 0.f)
	{
		const FRotator MovementRotation = (MovementDirection * MovementSpeed * DeltaSeconds).Rotation();
		SetActorRotation(MovementRotation);
	}
}

void ABasePawn::FireShot(FVector FireDirection)
{
	// If fire stick is pressed in any direction
	if (FireDirection.SizeSquared() > 0.0f)
	{
		const FRotator FireRotation = FireDirection.Rotation();
		const FVector ProjectileLocation = GetActorLocation() + FireRotation.RotateVector(ShootPoint->GetRelativeLocation());

		// ToDo: Object Pooling
		if (ProjectileClass)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = this;

			ABaseProjectile* Projectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileClass, ProjectileLocation, FireRotation, SpawnParameters);
		}

		// Allow shooting again after some delay
		bCanFire = false;
		FTimerHandle ShotTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(ShotTimerHandle, FTimerDelegate::CreateLambda([&] { bCanFire = true; }), FireRate, false);
	}
}

void ABasePawn::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
}