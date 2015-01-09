

#include "Demo.h"
#include "BatteryPickup.h"


ABatteryPickup::ABatteryPickup(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Base power level of battery
	PowerLevel = 150.0f;
}

void ABatteryPickup::OnPickedUp_Implementation()
{
	// Call parent implementation of onpickedup
	Super::OnPickedUp_Implementation();
	
	// Destroy the battery
	Destroy();

}


