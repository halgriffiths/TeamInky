// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSpawner.h"
#include "FPSObjectiveActor.h"

// Sets default values
APowerUpSpawner::APowerUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetHidden(true);
}

// Called when the game starts or when spawned
void APowerUpSpawner::BeginPlay()
{
	Super::BeginPlay();

	SpawnPowerUp();
}

void APowerUpSpawner::OnPowerUpPickUp()
{
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindUFunction(this, FName("SpawnPowerUp"));
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 2.f, false);
}

void APowerUpSpawner::SpawnPowerUp()
{
	FActorSpawnParameters SpawnInfo;
	AFPSObjectiveActor* SpawnedPowerUpRef = GetWorld()->SpawnActor<AFPSObjectiveActor>(AFPSObjectiveActor::StaticClass(), GetActorLocation(), FRotator(0, 0, 0), SpawnInfo);
	if (SpawnedPowerUpRef)
	{
		SpawnedPowerUpRef->PowerUpSpawner = this;
	}
}