// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "MovingActor.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;//enable 
	this->Speed = 190.5f;
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

	this->GlobalStartLocation = GetActorLocation();
	this->GlobalTargetLocation = GetTransform().TransformPosition(this->TargetLocation);
	this->LengthStart2Target = (this->GlobalTargetLocation - this->GlobalStartLocation).Size();

};
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (this->ActiveTriggers > 0)
	{

	if (HasAuthority())	//code will on run server side then it will replicate to client side if SetReplicates(true) and SetReplicateMovement(true)
	{
		//FVector Location{ GetActorLocation() };	 
		FVector Direction{ (this->GlobalTargetLocation - this->GlobalStartLocation).GetSafeNormal()};
		FVector NewLocation = (Speed * DeltaTime * Direction)+GetActorLocation();
		if ((NewLocation-GlobalStartLocation).Size()> this->LengthStart2Target)Swap(GlobalStartLocation, GlobalTargetLocation);
		SetActorLocation(NewLocation);
	};

	}

};

void AMovingActor::AddActiveTrigger()
{
	++this->ActiveTriggers;
};

void AMovingActor::RemoveActiveTrigger()
{
	if (this->ActiveTriggers > 0)--this->ActiveTriggers;
};

