// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpSpawner.h"
#include "FPSObjectiveActor.h"

// Sets default values
APowerUpSpawner::APowerUpSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnLocations.Add(FVector(-180, 270, 200));
	SpawnLocations.Add(FVector(-200, 300, 200));
}

// Called when the game starts or when spawned
void APowerUpSpawner::BeginPlay()
{
	Super::BeginPlay();

	// Spawn a PowerUp at every location
	int n = SpawnLocations.Num();
	for (int i = 0; i < n; ++i)
	{
		SpawnPowerUp(SpawnLocations[i]);
	}
	
}

// Called every frame
void APowerUpSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerUpSpawner::OnPowerUpPickUp(FVector Location)
{
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindUFunction(this, FName("SpawnPowerUp"), Location);
	GetWorldTimerManager().SetTimer(TimerHandle, TimerDel, 2.f, false);


	UE_LOG(LogTemp, Warning, TEXT("AHA, I picked up something!"));
}

void APowerUpSpawner::SpawnPowerUp(FVector Location)
{
	FActorSpawnParameters SpawnInfo;
	GetWorld()->SpawnActor<AFPSObjectiveActor>(AFPSObjectiveActor::StaticClass(), Location, FRotator(0, 0, 0), SpawnInfo);

}
