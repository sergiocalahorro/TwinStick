// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseProjectile.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class TWINSTICK_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ABaseProjectile();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Function called whenever this Actor collides with another Actor
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:	
	
	// Components
	UPROPERTY(EditAnywhere, Category = "Projectile")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;
};