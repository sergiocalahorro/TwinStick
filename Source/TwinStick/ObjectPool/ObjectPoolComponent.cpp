// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectPoolComponent.h"
#include "BasePoolableObject.h"

// Sets default values for this component's properties
UObjectPoolComponent::UObjectPoolComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UObjectPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	CreatePool();
}

// Called every frame
void UObjectPoolComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/*
 * Create object pool
 */
void UObjectPoolComponent::CreatePool()
{
	if (PoolableObjectClass)
	{
		for (int i = 0; i < PoolSize; i++)
		{
			ABasePoolableObject* PoolableObject = GetWorld()->SpawnActor<ABasePoolableObject>(PoolableObjectClass, FVector().ZeroVector, FRotator().ZeroRotator);
			PoolableObject->Deactivate();
			ObjectPool.Add(PoolableObject);
		}
	}
}

/*
 * Retrieve an object from pool
 * @return	Object from pool
 */
ABasePoolableObject* UObjectPoolComponent::GetPoolableObject()
{
	for (ABasePoolableObject* PoolableObject : ObjectPool)
	{
		if (!PoolableObject->IsActive())
		{
			return PoolableObject;
		}
	}

	return nullptr;
}

/*
 * Destroy all objects in pool
 */
void UObjectPoolComponent::DestroyObjectsInPool()
{
	for (ABasePoolableObject* PoolableObject : ObjectPool)
	{
		if (PoolableObject)
		{
			PoolableObject->Destroy();
		}
	}

	ObjectPool.Empty();
}