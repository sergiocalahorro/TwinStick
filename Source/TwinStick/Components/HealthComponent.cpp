// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "../TwinStickGameModeBase.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::TakeDamage);
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

/**
 * Function called whenever this component's owner takes any damage
 * @param	DamagedActor - Actor that received the damage
 * @param	Damage - Damage amount
 * @param	DamageType - Type of the damage that was received
 * @param	Instigator - Damage causer's controller
 * @param	DamageCauser - Actor that caused the damage
 */
void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	// Abort function if damage is equal or less than zero
	if (Damage <= 0.f)
	{
		return;
	}

	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
	if (IsDead())
	{	
		if (ATwinStickGameModeBase* TwinStickGameMode = Cast<ATwinStickGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			TwinStickGameMode->ActorDied(DamagedActor);
		}
	}
}

/**
 * Check if the component's owner is or not dead
 * @return	true if health is equal to zero
 */
bool UHealthComponent::IsDead() const
{
	return Health == 0.f;
}