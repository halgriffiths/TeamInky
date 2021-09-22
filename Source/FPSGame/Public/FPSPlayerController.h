// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FPSPlayerController.generated.h"

class APawn;

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "PlayerController")
	void OnGameOver();

	UPROPERTY(BlueprintReadWrite)
	bool bIsPacMan;

	UPROPERTY(BlueprintReadWrite)
	APawn* PreviousPawn;
	
};
