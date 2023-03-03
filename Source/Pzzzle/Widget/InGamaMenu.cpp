// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "InGamaMenu.h"
#include "Components/Button.h"


bool UInGamaMenu::Initialize()
{
	bool bSuper = Super::Initialize();
	if (!bSuper)return bSuper;
	this->Quit->OnClicked.AddDynamic(this, &UInGamaMenu::OnQuit);
	this->Resume->OnClicked.AddDynamic(this, &UInGamaMenu::OnResume);
	return true;
};

void UInGamaMenu::OnQuit()
{
	UE_LOG(LogTemp, Error, TEXT("Quit Pressed!"))
	GetGameInstance()->GetFirstLocalPlayerController()->ClientTravel("'/Game/ThirdPersonCPP/Maps/Lobby'", ETravelType::TRAVEL_Absolute);

};

void UInGamaMenu::OnResume()
{
	FInputModeGameOnly mode;
	mode.SetConsumeCaptureMouseDown(true);
	GetGameInstance()->GetFirstLocalPlayerController()->SetInputMode(mode);
	GetGameInstance()->GetFirstLocalPlayerController()->bShowMouseCursor=false;
	this->RemoveFromViewport();

};

