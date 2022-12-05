// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#include "PzzzleGameInstance.h"
#include"Engine/Engine.h"
#include"UObject/ConstructorHelpers.h"
#include"Actor/PlatformTrigger.h"
#include"Blueprint/UserWidget.h"
#include"Widget/MainMenu.h"
#include"OnlineSubsystem.h"
#include"OnlineSessionSettings.h"
#include"Interfaces/OnlineSessionInterface.h"

const static FName SESSION_NAME = TEXT("Session Main");

UPzzzleGameInstance::UPzzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuClass(TEXT("'/Game/UI/MenuSystem/WP_menu'"));
	if (MenuClass.Class == nullptr)return;
	this->Menu = MenuClass.Class;
	//	UE_LOG(LogTemp,Warning,TEXT("Found Class %s"),*Menu->GetName())
};

void  UPzzzleGameInstance::Init()
{
	Super::Init();
	IOnlineSubsystem* System = IOnlineSubsystem::Get();
	if (System == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Subsystem Found!"))

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[Init] Subsystem  %s"), *System->GetSubsystemName().ToString())
			SessionInterface = System->GetSessionInterface();
		if (SessionInterface)
		{
			UE_LOG(LogTemp, Error, TEXT("Session Interface Found!"))
				SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPzzzleGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPzzzleGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPzzzleGameInstance::OnSessionSearchComplete);
			this->SessionSearch = MakeShareable(new FOnlineSessionSearch);
			if (SessionSearch.IsValid())
			{
				UE_LOG(LogTemp,Error,TEXT("Session Searching Started..."))
				SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
			}
		}
	}
}

void UPzzzleGameInstance::Host()
{

	if (this->SessionInterface.IsValid())
	{

		auto ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		this->GetFirstLocalPlayerController()->ClientTravel("/Game/Loading", ETravelType::TRAVEL_Relative);
		if (ExistingSession != nullptr)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			this->CreateSession();
		}

	}

};

void UPzzzleGameInstance::Join(const FString& Address)
{
	UEngine* Engine = GetEngine();
	//	if (Engine == nullptr)return;
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController == nullptr)return;
	FInputModeGameOnly Mode;
	Mode.SetConsumeCaptureMouseDown(true);
	PlayerController->SetInputMode(Mode);
	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	if (Engine)
		Engine->AddOnScreenDebugMessage(0, 2.5f, FColor::Green, (Address));
};

void UPzzzleGameInstance::LoadMenu()
{
	if (this->Menu == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("No Widget Class  /Game/UI/MenuSystem/"));
		return;
	};
	UMainMenu* Widget = CreateWidget<UMainMenu>(this, this->Menu);
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
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

void UPzzzleGameInstance::OnCreateSessionComplete(FName SessionName, bool Success)
{
	if (!Success)
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to Create a new Session!"));
		return;
	};
	UEngine* Engine = GetEngine();
	if (Engine == nullptr)return;
	Engine->AddOnScreenDebugMessage(0, 2.5f, FColor::Black, FString("Hosting Game..."));
	UWorld* World = GetWorld();
	FInputModeGameOnly Mode;
	Mode.SetConsumeCaptureMouseDown(true);
	GetFirstLocalPlayerController()->SetInputMode(Mode);
	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");

};

void UPzzzleGameInstance::CreateSession()
{
	if (this->SessionInterface.IsValid())
	{

		FOnlineSessionSettings SessionSettings;
		SessionInterface->CreateSession(0, SESSION_NAME, SessionSettings);
	}
};

void UPzzzleGameInstance::OnDestroySessionComplete(FName SessionName, bool Success)
{
	if (Success)
	{
		this->CreateSession();
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Failed to Destryo Session "))
	};

};

void UPzzzleGameInstance::OnSessionSearchComplete(bool Success)
{
	UE_LOG(LogTemp,Error,TEXT("Session Searching Done!"))
};

