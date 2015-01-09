

#include "Demo.h"
#include "DemoHUD.h"


ADemoHUD::ADemoHUD(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Use the RobotoDistanceField font from the engine
	static ConstructorHelpers::FObjectFinder<UFont>HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));
	HUDFont = HUDFontOb.Object;

}

void ADemoHUD::DrawHUD()
{
	// Get screen dimensions
	FVector2D ScreenDimensions = FVector2D(Canvas->SizeX, Canvas->SizeY);

	// Call to the parent versions of DrawHUD
	Super::DrawHUD();

	// Get the character and print its power level
	ADemoCharacter* MyCharacter = Cast<ADemoCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
	FString sPowerLevel = FString::Printf(TEXT("%10.1f"), FMath::Abs(MyCharacter->PowerLevel));
	DrawText(sPowerLevel, FColor::White, 50, 50, HUDFont);

	ADemoGameMode* MyGameMode = Cast<ADemoGameMode>(UGameplayStatics::GetGameMode(this));

	// If the game is over
	if (MyGameMode->GetCurrentState() == EDemoPlayState::EGameOver)
	{
		// Create a variable for storing the size of printing 'Game Over'
		FVector2D GameOverSize;
		GetTextSize(TEXT("Game Over"), GameOverSize.X, GameOverSize.Y, HUDFont);
		DrawText(TEXT("Game Over"), FColor::White, (ScreenDimensions.X - GameOverSize.X) / 2.0f, (ScreenDimensions.Y - GameOverSize.Y) / 2.0f, HUDFont);
		
	}
}

