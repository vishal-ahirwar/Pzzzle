// Copyright(c)2022 Vishal Ahirwar. All rights reserved.

#include "PlatformTrigger.h"
#include"Components/BoxComponent.h"
#include"MovingActor.h"
// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("Trigger Volume"));
	if (TriggerVolume == nullptr)return;
	RootComponent = TriggerVolume;
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::BeginOverlap);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::EndOverlap);
}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

};
void APlatformTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("Volume Activated..."));
	for (const auto& actor : this->Triggers)
	{
		if (actor != nullptr)actor->AddActiveTrigger();
	};
};
void APlatformTrigger::EndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Volume Deactiveted!"));
	for (const auto& actor : this->Triggers)
	{
		if (actor != nullptr)actor->RemoveActiveTrigger();
	};
};



