// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TwinStickGameModeBase.generated.h"

class ABasePawn;
class ABasePlayerController;

/**
 * 
 */
UCLASS()
class TWINSTICK_API ATwinStickGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	// Constructor
	ATwinStickGameModeBase();

	// Actor in game died
	void ActorDied(AActor* DeadActor);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent)
	void StartGame(); void StartGame_Implementation();

	UFUNCTION(BlueprintNativeEvent)
	void GameOver(bool bWonGame); void GameOver_Implementation(bool bWonGame);

private:

	void HandleGameStart();

private:

	ABasePawn* BasePawn;
	ABasePlayerController* BasePlayerController;
};