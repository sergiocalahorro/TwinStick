// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePoolableObject.generated.h"

UCLASS()
class TWINSTICK_API ABasePoolableObject : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ABasePoolableObject();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Set the lifespan of this actor
	virtual void SetLifeSpan(float NewLifeSpan) override;

	// Check wheter this object is or not active
	bool IsActive() const;

	// Activate object
	virtual void Activate();

	// Deactivate object
	virtual void Deactivate();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	bool bIsActive;
	float LifeSpan;
	FTimerHandle LifeSpanTimer;
};