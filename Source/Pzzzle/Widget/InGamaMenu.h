// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InGamaMenu.generated.h"

/**
 * 
 */
UCLASS()
class PZZZLE_API UInGamaMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	bool Initialize()override;
private:
	UPROPERTY(meta=(BindWidget))
	class UButton* Quit;

	UPROPERTY(meta = (BindWidget))
		class UButton* Resume;
private:
	UFUNCTION()
	void OnQuit();

	UFUNCTION()
	void OnResume();


	
};
