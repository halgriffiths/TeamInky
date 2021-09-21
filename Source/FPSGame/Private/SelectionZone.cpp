// Fill out your copyright notice in the Description page of Project Settings.


#include "SelectionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Pawn.h"
#include "FPSPlayerController.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "FPSPlayerController.h"

// Sets default values
ASelectionZone::ASelectionZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &ASelectionZone::HandleOverlap);
	OverlapComp->OnComponentEndOverlap.AddDynamic(this, &ASelectionZone::OnOverlapEnd);


	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(RootComponent);

	CurrentOccupiers = 0;
}



void ASelectionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	// Check if a Pawn overlapped with the zone
	APawn* InstigatorPawn = Cast<APawn>(OtherActor);

	if (InstigatorPawn)
	{
		CurrentOccupiers++;

		// Get the Controller that is posessing the Pawn

		AFPSPlayerController* ControllerInstigator = Cast<AFPSPlayerController>(InstigatorPawn->GetController());

		if (ControllerInstigator)
		{
			OccupyingController = ControllerInstigator;
			if (bIsPacManZone)
			{
				ControllerInstigator->bIsPacMan = true;
			}

			AFPSGameMode* GM = Cast<AFPSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

			if (GM)
			{
				GM->OnPlayerEnterSelectionZone(ControllerInstigator);
			}
		}

		UE_LOG(LogTemp, Log, TEXT("Overlapped with selection zone!"));

	}

}

void ASelectionZone::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* InstigatorPawn = Cast<APawn>(OtherActor);

	if (InstigatorPawn)
	{
		CurrentOccupiers --;
		OccupyingController = nullptr;

		AFPSPlayerController* ControllerInstigator = Cast<AFPSPlayerController>(InstigatorPawn->GetController());

		if (ControllerInstigator)
		{
			OccupyingController = ControllerInstigator;
			if (bIsPacManZone)
			{
				ControllerInstigator->bIsPacMan = false;
			}
		}
	}
}
