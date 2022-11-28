// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class PZZZLE_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

protected:
	bool Initialize()override;
private:
	UPROPERTY(meta = (BindWidget))
		class UButton* Host;
	UPROPERTY(meta = (BindWidget))
		class UButton* Join;
	UPROPERTY(meta = (BindWidget))
		class UButton* Quit;
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* WidgetSwitcher;
	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	class IMenuInterface* MenuInterface;
public:
	void SetMenuInterface(class IMenuInterface*);
private:
	UFUNCTION()
	void OnHost();
	
	UFUNCTION()
	void OpenJoinMenu();

	UFUNCTION()
	void OnQuit();
};
