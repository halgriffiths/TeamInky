// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUpSpawner.generated.h"

UCLASS()
class FPSGAME_API APowerUpSpawner : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	APowerUpSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void OnPowerUpPickUp();

	UFUNCTION(BlueprintImplementableEvent)
	void SpawnPowerUp();

	/* Handle to manage the timer */
	//FTimerHandle TimerHandle;


};
