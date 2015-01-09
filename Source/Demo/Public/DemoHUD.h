

#pragma once

#include "GameFramework/HUD.h"

#include "Engine/Canvas.h"
#include "Engine/Font.h"
#include "DemoGameMode.h"
#include "DemoCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "DemoHUD.generated.h"

/**
 * 
 */
UCLASS()
class DEMO_API ADemoHUD : public AHUD
{
	GENERATED_UCLASS_BODY()

	// Variable for storing the font
	UPROPERTY() // This won't be garbage collected, wont' destroy validity when checking font
	UFont* HUDFont;
	
	// Primary draw call fro the HUD
	virtual void DrawHUD();


};
