// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "Demo.h"
#include "DemoGameMode.h"
#include "DemoCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DemoHUD.h"

ADemoGameMode::ADemoGameMode(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/MyCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Set the default HUD class
	HUDClass = ADemoHUD::StaticClass();

	// Base decay rate
	DecayRate = 0.25f;
}

void ADemoGameMode::Tick(float DeltaSeconds)
{
	ADemoCharacter *MyCharacter = Cast<ADemoCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));

	// If the character still has power
	if (MyCharacter->PowerLevel > 0.05f)
	{
		// Decrease player's power
		MyCharacter->PowerLevel = FMath::FInterpTo(MyCharacter->PowerLevel, 0.0f, DeltaSeconds, DecayRate);
	}
	else
	{
		SetCurrentState(EDemoPlayState::EGameOver);
	}
}

void ADemoGameMode::SetCurrentState(EDemoPlayState NewState)
{
	CurrentState = NewState;

	HandleNewState(NewState);
}

void ADemoGameMode::HandleNewState(EDemoPlayState NewState)
{
	switch (NewState)
	{
		// When playing, spawn volumes will be able to spawn
		case EDemoPlayState::EPlaying:
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->EnableSpawning();
			}

			break;
		// When we are not playing, spawn volumes should deactivate
		case EDemoPlayState::EGameOver:
		{
			for (ASpawnVolume* Volume : SpawnVolumeActors)
			{
				Volume->DisableSpawning();
			}

			APlayerController *PlayerController = UGameplayStatics::GetPlayerController(this, 0);
			PlayerController->SetCinematicMode(true, true, true);
		}

			break;
		case EDemoPlayState::EUnknown:
			// Do nothing
			break;
	}
}

void ADemoGameMode::BeginPlay()
{
	// Inherit parent function 
	Super::BeginPlay();

	// Find all spawn colume actors
	TArray<AActor*> FoundActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);

		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.Add(SpawnVolumeActor);
		}
	}

	SetCurrentState(EDemoPlayState::EPlaying);
}
