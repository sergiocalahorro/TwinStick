// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;
class UInputComponent;
class ABaseProjectile;

UCLASS()
class TWINSTICK_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	ABasePawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Movement
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void UpdatePawnRotation(float DeltaSeconds);

	// Shooting
	void FireForward(float AxisValue);
	void FireRight(float AxisValue);
	void FireShot(FVector FireDirection);

private:

	// Parameters
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MovementSpeed = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Shoot")
	float FireRate = 0.2f;

	UPROPERTY(VisibleAnywhere, Category = "Shoot")
	bool bCanFire = true;
	
	UPROPERTY(EditAnywhere, Category = "Shoot")
	TSubclassOf<ABaseProjectile> ProjectileClass;

	// Components
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Camera")
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere, Category = "Shoot")
	USceneComponent* ShootPoint;

	UPROPERTY(EditAnywhere, Category = "Components")
	UHealthComponent* HealthComponent;

	// Inputs
	float MoveForwardValue;
	float MoveRightValue;
	float FireForwardValue;
	float FireRightValue;
};