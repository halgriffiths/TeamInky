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
#include "GenericPlatform/GenericPlatformMath.h"


AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();

	bIsGameRunning = false;
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
		if (Zone->CurrentOccupiers  == 1)
		{
			OccupiedZones++;
		}
	}

	TArray<AActor*> ReturnedActors;
	UGameplayStatics::GetAllActorsOfClass(this, AFPSPlayerController::StaticClass(), ReturnedActors);

	if (bHasPacMan && !bIsGameRunning && OccupiedZones == FGenericPlatformMath::Min(ReturnedActors.Num(), 5) && OccupiedZones >= 3)
	{
		StartGame();
	}
}

void AFPSGameMode::StartGame()
{
	for (ASelectionZone* Zone : TActorRange<ASelectionZone>(GetWorld()))
	{
		if (Zone->OccupyingController)
		{
			Zone->SpawnCharacter();
		}
	}

	bIsGameRunning = true;
	AFPSGameMode::StartTimer();
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
