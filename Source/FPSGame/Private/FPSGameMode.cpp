// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"
#include "SelectionZone.h"
#include "FPSPlayerController.h"
#include "EngineUtils.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}


void AFPSGameMode::OnPlayerEnterSelectionZone(AFPSPlayerController* ControllerInstigator)
{

	if (ControllerInstigator->bIsPacMan)
	{
		bHasPacMan = true;
	}

	CheckStartingConditions();
}

void AFPSGameMode::CheckStartingConditions()
{
	// If the number of occupied zones == the number of players and we have a PacMan we are good to go.
	int OccupiedZones = 0;
	for (ASelectionZone* Zone : TActorRange<ASelectionZone>(GetWorld()))
	{
		if (Zone->bIsOccupied)
		{
			OccupiedZones++;
		}
	}

	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFPSPlayerController::StaticClass(), ReturnedActors);

	if (bHasPacMan && OccupiedZones == ReturnedActors.Num())
	{
		StartGame();
	}
}

void AFPSGameMode::StartGame()
{
	// Iterate over all PlayerControllers and make them posses a Pawn that is in the PacManMap.

	for (AFPSPlayerController* Controller : TActorRange<AFPSPlayerController>(GetWorld()))
	{
		if (Controller->bIsPacMan)
		{
			// Posses PacMan
			// Currently BP implementation because idk if it's possible to get a reference to a BP class in C++.
			PossesPacMan(Controller);
		}
		else
		{
			// Posess a Ghost
			// Currently BP implementation because idk if it's possible to get a reference to a BP class in C++.
			PossesGhost(Controller);
		}
	}
	
}

void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool bMissionSuccess)
{
	if (InstigatorPawn)
	{
		if (SpectatingViewpointClass)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewpointClass, ReturnedActors);

			// Change viewtarget if any valid actor found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
				{
					APlayerController* PC = It->Get();
					if (PC)
					{
						PC->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("SpectatingViewpointClass is nullptr. Please update GameMode class with valid subclass. Cannot change spectating view target."));
		}
	}

	AFPSGameState* GS = GetGameState<AFPSGameState>();
	if (GS)
	{
		GS->MulticastOnMissionComplete(InstigatorPawn, bMissionSuccess);
	}


	OnMissionCompleted(InstigatorPawn, bMissionSuccess);
}
