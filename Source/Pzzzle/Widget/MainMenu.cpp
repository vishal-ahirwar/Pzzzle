// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "MainMenu.h"
#include "Components/Button.h"
#include"../MenuSystem/MenuInterface.h"
#include "Kismet/GameplayStatics.h"
bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)return false;
	
	if(this->Host!=nullptr)
	this->Host->OnClicked.AddDynamic(this,&UMainMenu::OnHost);

	if (this->Join != nullptr)
		this->Join->OnClicked.AddDynamic(this,&UMainMenu::OnJoin);

	if (this->Quit != nullptr)
		this->Quit->OnClicked.AddDynamic(this, &UMainMenu::OnQuit);
	return true;
};

void UMainMenu::OnHost()
{
	if (this->MenuInterface != nullptr)
		this->MenuInterface->Host();
	UE_LOG(LogTemp,Warning,TEXT("Host button pressed!"))
};

void UMainMenu::OnJoin()
{
	//if (this->menuinterface != nullptr)
	//	this->menuinterface->join();

	UE_LOG(LogTemp,Warning,TEXT("Join button Pressed!"))
};

void UMainMenu::OnQuit()
{
	UE_LOG(LogTemp, Warning, TEXT("Quit button Pressed!"))
};

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface_)
{
	this->MenuInterface = MenuInterface_;
};
