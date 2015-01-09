

#include "Demo.h"
#include "SpawnVolume.h"
#include "Pickup.h"


ASpawnVolume::ASpawnVolume(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Create the simple StaticMeshComponent to represent the pickup in the level
	WhereToSpawn = PCIP.CreateDefaultSubobject<UBoxComponent>(this, TEXT("WhereToSpawn"));

	// Set the StaticMeshComponent as the root component
	RootComponent = WhereToSpawn;

	// Set the spawn delay range
	SpawnDelayRangeLow = 1.0f;
	SpawnDelayRangeHigh = 4.5f;
	SpawnDelay = GetRandomSpawnDelay();

	// Make the SpawnVolume tickable
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnVolume::SpawnPickup()
{
	// Check if we have set something to spawn
	if (WhatToSpawn != NULL)
	{
		// Check for a valid world
		UWorld* const World = GetWorld();

		if (World)
		{
			// Set spawn params
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Get a random location to spawn at
			FVector SpawnLocation = GetRandomPointInVolume();

			// Get a random rotation for the spawned item
			FRotator SpawnRotation;
			SpawnRotation.Yaw = FMath::FRand() * 360.0f;
			SpawnRotation.Pitch = FMath::FRand() * 360.0f;
			SpawnRotation.Roll = FMath::FRand() * 360.0f;

			// Spawn the pickup
			APickup* const SpawnedPickup = World->SpawnActor<APickup>(WhatToSpawn, SpawnLocation, SpawnRotation, SpawnParams);
		}
	}
}

float ASpawnVolume::GetRandomSpawnDelay()
{
	// Get a random float that falls within the spawn delay range
	return FMath::FRandRange(SpawnDelayRangeLow, SpawnDelayRangeHigh);
}

FVector ASpawnVolume::GetRandomPointInVolume()
{
	FVector RandomLocation;
	float MinX, MinY, MinZ;
	float MaxX, MaxY, MaxZ;

	FVector Origin;
	FVector BoxExtent;

	// Get the SpawnColume's origin and box extent
	Origin = WhereToSpawn->Bounds.Origin;
	BoxExtent = WhereToSpawn->Bounds.BoxExtent;

	// Calculate the minimum X, Y, and Z
	MinX = Origin.X - BoxExtent.X / 2.0f;
	MinY = Origin.Y - BoxExtent.Y / 2.0f;
	MinZ = Origin.Z - BoxExtent.Z / 2.0f;

	MaxX = Origin.X + BoxExtent.X / 2.0f;
	MaxY = Origin.Y + BoxExtent.Y / 2.0f;
	MaxZ = Origin.Z + BoxExtent.Z / 2.0f;

	// The random spawn location will fall between the min and max X, Y, and Z
	RandomLocation.X = FMath::FRandRange(MinX, MaxX);
	RandomLocation.Y = FMath::FRandRange(MinY, MaxY);
	RandomLocation.Z = FMath::FRandRange(MinZ, MaxZ);

	// Return the random spawn location
	return RandomLocation;
}

void ASpawnVolume::Tick(float DeltaSeconds)
{
	// If spawning is not enabled, do nothing
	if (!bSpawningEnabled)
	{
		return;
	}
	
	// Always add dela time to our spawn time
	SpawnTime += DeltaSeconds;

	bool bShouldSpawn = (SpawnTime > SpawnDelay);

	if (bShouldSpawn)
	{
		SpawnPickup();

		// Deduct spawn delay from accumulated time value
		SpawnTime -= SpawnDelay;

		SpawnDelay = GetRandomSpawnDelay();
	}
}

void ASpawnVolume::EnableSpawning()
{
	bSpawningEnabled = true;
}

void ASpawnVolume::DisableSpawning()
{
	bSpawningEnabled = false;
}