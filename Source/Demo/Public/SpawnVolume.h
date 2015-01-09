

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ASpawnVolume : public AActor
{
	GENERATED_UCLASS_BODY()

	// BoxComponent to specify the spawning area within the level
	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
	TSubobjectPtr<UBoxComponent> WhereToSpawn;

	// THe pickup to spawn
	UPROPERTY(EditAnywhere, Category = Spawning)
	TSubclassOf<class APickup> WhatToSpawn;

	// Minimum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelayRangeLow;

	// Maximum spawn delay
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
	float SpawnDelayRangeHigh;
	
	// Finds a random point within the BoxComponent
	UFUNCTION(BlueprintPure, Category = Spawning)
	FVector GetRandomPointInVolume();

	virtual void Tick(float DeltaSeconds);

	void EnableSpawning();
	void DisableSpawning();

private:

	// Whether or not spawning is enabled
	bool bSpawningEnabled;

	// The current spawn delay
	float SpawnDelay;

	// The time for when to spawn the pickup
	float SpawnTime;

	// Spawn pickup
	void SpawnPickup();

	// Calculates random spawn delay
	float GetRandomSpawnDelay();
};
