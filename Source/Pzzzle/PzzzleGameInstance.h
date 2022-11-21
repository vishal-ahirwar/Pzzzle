// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PzzzleGameInstance.generated.h"


UCLASS()
class PZZZLE_API UPzzzleGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UFUNCTION(Exec)
		void Host();

	UFUNCTION(Exec)
		void Join(const FString&Address);
public:
	UPzzzleGameInstance(const FObjectInitializer&);
	void Init()override;
private:

};
