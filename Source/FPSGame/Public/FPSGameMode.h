// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

class AFPSPlayerController;

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	bool bHasPacMan;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
	TSubclassOf<AActor> SpectatingViewpointClass;

public:

	AFPSGameMode();

	void CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess);

	void OnPlayerEnterSelectionZone(AFPSPlayerController* ControllerInstigator);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void PossesPacMan(AFPSPlayerController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void PossesGhost(AFPSPlayerController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
	void OnMissionCompleted(APawn* InstigatorPawn, bool bMissionSuccess);

	void CheckStartingConditions();

	void StartGame();
};



