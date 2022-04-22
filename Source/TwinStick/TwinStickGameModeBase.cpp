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

void ATwinStickGameModeBase::HandleGameStart()
{
	BasePawn = Cast<ABasePawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	BasePlayerController = Cast<ABasePlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	StartGame();
}

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

void ATwinStickGameModeBase::StartGame_Implementation()
{
	// ToDo
}

void ATwinStickGameModeBase::GameOver_Implementation(bool bWonGame)
{
	// ToDo
}