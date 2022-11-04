// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "MovingActor.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;//enable tick
	this->Speed = 10.5f;
	SetMobility(EComponentMobility::Movable);
};
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("[C++]Code Running on Server Side..."));
		SetReplicates(true);	//enable replication to the client side from server side
		SetReplicateMovement(true);	//enable movement replication to the client side from server side
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("[C++]Code Running on Client Side..."));
	};


};
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (HasAuthority())	//code will on run server side then it will replicate to client side if SetReplicates(true) and SetReplicateMovement(true)
	{
		FVector Location{ GetActorLocation() };	 
		FVector GlobalTargetLocation = GetTransform().TransformPosition(this->TargetLocation);
		FVector Direction{ (GlobalTargetLocation - Location).GetSafeNormal()};
		Location += (Speed * DeltaTime * Direction);
		SetActorLocation(Location);
	};

};
