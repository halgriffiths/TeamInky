// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportZone.h"
#include "Components/BoxComponent.h"
#include "FPSCharacter.h"


// Sets default values
ATeleportZone::ATeleportZone()
{
	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComp->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComp;

	OverlapComp->SetHiddenInGame(false);

}

