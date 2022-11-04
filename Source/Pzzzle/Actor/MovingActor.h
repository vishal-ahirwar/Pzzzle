// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingActor.generated.h"

/**
 * 
 */
UCLASS()
class PZZZLE_API AMovingActor : public AStaticMeshActor
{
	GENERATED_BODY()
public:
	AMovingActor();
public:
	UPROPERTY(EditAnyWhere)
		float Speed;
	UPROPERTY(EditAnyWhere, Meta = (MakeEditWidget = true))
		FVector TargetLocation;
private:
	FVector GlobalStartLocation;
	FVector GlobalTargetLocation;
	float LengthStart2Target;

protected:
	void BeginPlay()override;
	void Tick(float)override;
};
