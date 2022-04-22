// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICK_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	// Constructor
	ABasePlayerController();

	void SetPlayerEnabledState(bool bPlayerEnabled);

protected:

	virtual void BeginPlay() override;
};