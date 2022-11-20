// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "PzzzleGameInstance.h"
#include"Engine/Engine.h"
UPzzzleGameInstance::UPzzzleGameInstance(const FObjectInitializer&ObjectInitializer)
{
	UE_LOG(LogTemp,Warning,TEXT("[constructor]Pzzle API Instace running..."))
};

void  UPzzzleGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp,Warning,TEXT("[Init] Pzzle API instance running.."))
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
	Engine->AddOnScreenDebugMessage(0, 2.5f, FColor::Green, FString("Joining Server..."));
};
