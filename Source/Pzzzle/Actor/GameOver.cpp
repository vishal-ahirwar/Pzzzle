// Copyright(c)2022 Vishal Ahirwar. All rights reserved.


#include "GameOver.h"
#include"Components/BoxComponent.h"

// Sets default values
AGameOver::AGameOver()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	this->Trigger = CreateDefaultSubobject<UBoxComponent>(FName("Trigger"));
	if (!Trigger)return;
}

// Called when the game starts or when spawned
void AGameOver::BeginPlay()
{
	Super::BeginPlay();
	
}
