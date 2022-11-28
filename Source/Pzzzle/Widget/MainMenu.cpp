// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include"../MenuSystem/MenuInterface.h"
#include "Kismet/GameplayStatics.h"


bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success)return false;
	
	if(this->Host!=nullptr)
	this->Host->OnClicked.AddDynamic(this,&UMainMenu::OnHost);

	if (this->Join != nullptr)
		this->Join->OnClicked.AddDynamic(this,&UMainMenu::OpenJoinMenu);

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

void UMainMenu::OpenJoinMenu()
{
	if (this->WidgetSwitcher == nullptr|| this->JoinMenu==nullptr)return;

	this->WidgetSwitcher->SetActiveWidget(this->JoinMenu);

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
