// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#include "PzzzleGameInstance.h"
#include"Engine/Engine.h"
#include"UObject/ConstructorHelpers.h"
#include"Actor/PlatformTrigger.h"
#include"Blueprint/UserWidget.h"
#include"Widget/MainMenu.h"

UPzzzleGameInstance::UPzzzleGameInstance(const FObjectInitializer&ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClass(TEXT("'/Game/UI/MenuSystem/WP_menu'"));
	if (MenuClass.Class == nullptr)return;
	this->Menu = MenuClass.Class;
//	UE_LOG(LogTemp,Warning,TEXT("Found Class %s"),*Menu->GetName())
};

void  UPzzzleGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("[Init] Found Menu Widget Class %s"), *this->Menu->GetName())
}

void UPzzzleGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (Engine == nullptr)return;
	Engine->AddOnScreenDebugMessage(0, 2.5f, FColor::Black, FString("Hosting Game..."));
	UWorld* World = GetWorld();
	FInputModeGameOnly Mode;
	Mode.SetConsumeCaptureMouseDown(true);
	GetFirstLocalPlayerController()->SetInputMode(Mode);
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
};

void UPzzzleGameInstance::Join(const FString&Address)
{
	UEngine* Engine = GetEngine();
//	if (Engine == nullptr)return;
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr)return;
	FInputModeGameOnly Mode;
	Mode.SetConsumeCaptureMouseDown(true);
	PlayerController->SetInputMode(Mode);
	PlayerController->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
	if(Engine)
		Engine->AddOnScreenDebugMessage(0, 2.5f, FColor::Green, (Address));
};

void UPzzzleGameInstance::LoadMenu()
{
	if (this->Menu == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Widget Class  /Game/UI/MenuSystem/"));
		return;
	};
	UMainMenu*Widget=CreateWidget<UMainMenu>(this, this->Menu);
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if(PlayerController)
		PlayerController->bShowMouseCursor = true;

	if (Widget)
	{
		FInputModeUIOnly Mode;
	/*	Mode.SetWidgetToFocus(this->Menu.Get());*/

		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		PlayerController->SetInputMode(Mode);

		Widget->AddToViewport();
		Widget->bIsFocusable = true;
		Widget->SetMenuInterface(this);
	};

};


