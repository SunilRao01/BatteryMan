

#pragma once

#include "Pickup.h"
#include "BatteryPickup.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ABatteryPickup : public APickup
{
	GENERATED_UCLASS_BODY()

	// Set the power amount the battery gives to the player
	UPROPERTY(EditAnywhere, BlueprintREadWrite, Category = Power)
	float PowerLevel;
	
	// Overrides the PickedUp function (Use Implementation because this is a BlueprintNativeEvent)
	void OnPickedUp_Implementation();
};
