// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "SpawnVolume.h"
#include "DemoGameMode.generated.h"

// Enum to store current game state
enum class EDemoPlayState : uint8
{
	EPlaying,
	EGameOver,
	EUnknown
};

UCLASS(minimalapi)
class ADemoGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()
	
	virtual void Tick(float DelaSeconds);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Power)
	float DecayRate;

	EDemoPlayState GetCurrentState() const;

	void SetCurrentState(EDemoPlayState NewState);

	virtual void BeginPlay();

private:

	TArray<ASpawnVolume*> SpawnVolumeActors;

	EDemoPlayState CurrentState;

	void HandleNewState(EDemoPlayState NewState);
};

FORCEINLINE EDemoPlayState ADemoGameMode::GetCurrentState() const
{
	return CurrentState;
}

