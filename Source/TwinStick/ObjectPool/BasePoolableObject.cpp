// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePoolableObject.h"

// Sets default values
ABasePoolableObject::ABasePoolableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABasePoolableObject::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePoolableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Set the lifespan of this actor
void ABasePoolableObject::SetLifeSpan(float NewLifeSpan)
{
	LifeSpan = NewLifeSpan;
	GetWorldTimerManager().SetTimer(LifeSpanTimer, this, &ABasePoolableObject::Deactivate, LifeSpan, false);
}

/**
 * Check wheter this object is or not active
 * @return	true if is activated
 */
bool ABasePoolableObject::IsActive() const
{
	return bIsActive;
}

/**
 * Activate object
 */
void ABasePoolableObject::Activate()
{
	bIsActive = true;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

/**
 * Deactivate object
 */
void ABasePoolableObject::Deactivate()
{
	bIsActive = false;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}