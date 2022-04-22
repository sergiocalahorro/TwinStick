// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectPoolComponent.generated.h"

class ABasePoolableObject;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TWINSTICK_API UObjectPoolComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UObjectPoolComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Retrieve an object from pool
	ABasePoolableObject* GetPoolableObject();

	// Destroy all objects in pool
	void DestroyObjectsInPool();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// Create object pool
	void CreatePool();

private:

	UPROPERTY(EditAnywhere, Category = "Pool");
	TSubclassOf<ABasePoolableObject> PoolableObjectClass;

	UPROPERTY(EditAnywhere, Category = "Pool");
	int32 PoolSize;

	TArray<ABasePoolableObject*> ObjectPool;
};