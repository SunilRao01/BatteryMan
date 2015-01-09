

#pragma once

#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API APickup : public AActor
{
	GENERATED_UCLASS_BODY()

	// True when pickup is able to be picked up, false if something deactivates the pickup
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pickup)
	bool bIsActive;

	// Simple collision primitive to use as the rooot component
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<USphereComponent> BaseCollisionComponent;

	// Simple mesh primitive, required to modify mesh properties
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Pickup)
	TSubobjectPtr<UStaticMeshComponent> PickupMesh;
	
	// Function to call when the pickup is collected
	UFUNCTION(BlueprintNativeEvent)
	void OnPickedUp();
};
