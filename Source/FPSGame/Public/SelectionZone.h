// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SelectionZone.generated.h"

class UBoxComponent;

UCLASS()
class FPSGAME_API ASelectionZone : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ASelectionZone();

	UPROPERTY(EditAnywhere, Category = "Zone Type")
	bool bIsPacManZone;

	bool bIsOccupied;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UBoxComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDecalComponent* DecalComp;

	UFUNCTION()
	void HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
