// Copyright Epic Games, Inc. All Rights Reserved.


#include "TwinStickGameModeBase.h"
#include "Pawns/BasePawn.h"
#include "PlayerController/BasePlayerController.h"
#include "Kismet/GameplayStatics.h"

ATwinStickGameModeBase::ATwinStickGameModeBase()
{

}

void ATwinStickGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

/*
 * Setup game on start
 */
void ATwinStickGameModeBase::HandleGameStart()
{
	BasePawn = Cast<ABasePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	BasePlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	StartGame();
}

/*
 * Function called when an Actor in game died
 * @param	DeadActor - Actor that died
 */
void ATwinStickGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == BasePawn)
	{
		BasePawn->HandleDestruction();

		if (BasePlayerController)
		{
			BasePlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
}

/*
 * Function called when game is started
 */
void ATwinStickGameModeBase::StartGame_Implementation()
{
	// ToDo
}

/*
 * Function called when game is over
 * @param	bWonGame - true if player won the game
 */
void ATwinStickGameModeBase::GameOver_Implementation(bool bWonGame)
{
	// ToDo
}