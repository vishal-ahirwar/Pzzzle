// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#include "PzzzleGameInstance.h"
#include"Engine/Engine.h"
#include"UObject/ConstructorHelpers.h"
#include"Actor/PlatformTrigger.h"
#include"Blueprint/UserWidget.h"

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
	UE_LOG(LogTemp,Warning,TEXT("[Init] Found Menu Widget Class %s"),*this->Menu->GetName())
}

void UPzzzleGameInstance::Host()
{
	UEngine* Engine = GetEngine();
	if (Engine == nullptr)return;
	Engine->AddOnScreenDebugMessage(0, 2.5f, FColor::Black, FString("Hosting Game..."));
	UWorld* World = GetWorld();
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap");
};

void UPzzzleGameInstance::Join(const FString&Address)
{
	UEngine* Engine = GetEngine();
	if (Engine == nullptr)return;
	APlayerController* Controller = GetFirstLocalPlayerController();
	if (Controller == nullptr)return;
	Controller->ClientTravel(Address,ETravelType::TRAVEL_Absolute);
	Engine->AddOnScreenDebugMessage(0, 2.5f, FColor::Green, (Address));
};

void UPzzzleGameInstance::LoadMenu()
{
	if (this->Menu == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Widget Class  /Game/UI/MenuSystem/"));
		return;
	};
	UUserWidget*Widget=CreateWidget<UUserWidget>(this, this->Menu);
	if (Widget != nullptr)
		Widget->AddToViewport();
};
