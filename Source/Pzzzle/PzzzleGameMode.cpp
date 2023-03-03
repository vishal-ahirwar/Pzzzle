// Copyright Epic Games, Inc. All Rights Reserved.

#include "PzzzleGameMode.h"
#include "PzzzleCharacter.h"
#include "UObject/ConstructorHelpers.h"

APzzzleGameMode::APzzzleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
void APzzzleGameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->ToggleSpeaking(true);
}
