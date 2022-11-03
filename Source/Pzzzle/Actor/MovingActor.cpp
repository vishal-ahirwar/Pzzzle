// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "MovingActor.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	this->Speed = 10.5f;
	SetMobility(EComponentMobility::Movable);
};
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())UE_LOG(LogTemp,Warning, TEXT("Running on Server..."))
	else UE_LOG(LogTemp,Warning, TEXT("Running on Client..."));

};
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())
	{
		/*auto*/FVector Location = GetActorLocation();
		Location += FVector(Speed * DeltaTime, 0, 0);
		SetActorLocation(Location);
	};

};
