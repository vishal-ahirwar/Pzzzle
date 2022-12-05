// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include"MenuSystem/MenuInterface.h"
#include"OnlineSubsystem.h"
#include "PzzzleGameInstance.generated.h"


UCLASS()
class PZZZLE_API UPzzzleGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
protected:
	UFUNCTION(Exec, BluePrintCallable)
		void LoadMenu();

	UFUNCTION(Exec)
		void Host()override;

	UFUNCTION(Exec)
		void Join(const FString& Address)override;

	void OnCreateSessionComplete( FName,  bool);
	void CreateSession();
	void OnDestroySessionComplete(FName, bool);
	void OnSessionSearchComplete(bool);
public:
	UPzzzleGameInstance(const FObjectInitializer&);
	void Init()override;

private:
	TSubclassOf<class UUserWidget>Menu;
	TSharedPtr<class FOnlineSessionSearch>SessionSearch;
	IOnlineSessionPtr SessionInterface;
	
	//	APlayerController* PlayerController{ nullptr };
};
