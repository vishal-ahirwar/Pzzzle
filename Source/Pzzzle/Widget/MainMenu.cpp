// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableText.h"
#include "Components/EditableText.h"
#include"../MenuSystem/MenuInterface.h"
#include "Kismet/GameplayStatics.h"
#include"../MenuSystem/ServerRow.h"
#include"Components/ScrollBox.h"
#include"Components/TextBlock.h"

UMainMenu::UMainMenu(const FObjectInitializer&Object):Super(Object)
{

	ConstructorHelpers::FClassFinder<UUserWidget> ServerWidgetClass(TEXT("'/Game/Widget/WBP_Server'"));
	if (ServerWidgetClass.Class)this->ServerWidget = ServerWidgetClass.Class;
};

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();

	if (!Success)return false;
	
	if(this->Host!=nullptr)
	this->Host->OnClicked.AddDynamic(this,&UMainMenu::OnHost);

	if (this->Join != nullptr)
		this->Join->OnClicked.AddDynamic(this,&UMainMenu::OpenJoinMenu);

	//if (this->Quit != nullptr)
	//	this->Quit->OnClicked.AddDynamic(this, &UMainMenu::OnQuit);

	if (this->Back != nullptr)
		this->Back->OnClicked.AddDynamic(this, &UMainMenu::OnBack);

	if (this->Join_1 != nullptr)
		this->Join_1->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	if (this->QuitGame != nullptr)
		this->QuitGame->OnClicked.AddDynamic(this, &UMainMenu::FQuit);

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

	UE_LOG(LogTemp, Warning, TEXT("Join button Pressed!"))

		if (this->MenuInterface != nullptr)
		{
			this->MenuInterface->RefreshServerList();
		};

};

//void UMainMenu::OnQuit()
//{
//	UE_LOG(LogTemp, Warning, TEXT("Quit button Pressed!"))
//};

void UMainMenu::SetMenuInterface(IMenuInterface* MenuInterface_)
{
	this->MenuInterface = MenuInterface_;
};

void UMainMenu::OnBack()
{
	if (this->WidgetSwitcher == nullptr || this->MainMenu==nullptr)return;
	this->WidgetSwitcher->SetActiveWidget(this->MainMenu);
};

void UMainMenu::SetServerList(const TArray<FString>& ServerNames)
{
	this->ServerList->ClearChildren();
	for (const FString& Name : ServerNames)
	{
		UServerRow* ServerWid = CreateWidget<UServerRow>(this, this->ServerWidget);
		if (ServerWid)
		{
			ServerWid->Text->SetText(FText::FromString(Name));
			this->ServerList->AddChild(ServerWid);
		};

	};

}
void UMainMenu::JoinServer()
{
	//if (this->ip == nullptr)return;
	//ConstructorHelpers::FClassFinder<UUserWidget> ServerWidgetClass(TEXT("'/Game/UI/MenuSystem/WP_Server'"));
	//if (ServerWidgetClass.Class)this->ServerWidget = ServerWidgetClass.Class;
	if (this->ServerWidget)
	{
		UServerRow*Widget = CreateWidget<UServerRow>(GetWorld(),ServerWidget);
		this->ServerList->ClearChildren();
		if (Widget)
		{
			Widget->Text->SetText(FText::FromString("Searching ..."));
			ServerList->AddChild(Widget);
		}

	}
	if (this->MenuInterface == nullptr)return;

	this->MenuInterface->Join(/*this->ip->GetText().ToString()*/"");
	//UE_LOG(LogTemp,Warning,TEXT("Joining server at address %s"),*ip->GetText().ToString())
};

void UMainMenu::FQuit()
{
	UE_LOG(LogTemp, Error, TEXT("FQuit Pressed!"))
		GetGameInstance()->GetFirstLocalPlayerController()->ConsoleCommand(TEXT("quit"));
};
