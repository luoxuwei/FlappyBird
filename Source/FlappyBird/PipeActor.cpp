// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"
#include <Components/SceneComponent.h>

// Sets default values
APipeActor::APipeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	for (size_t i = 0; i < 3; i++)
	{
		USceneComponent *c = CreateDefaultSubobject<USceneComponent>(*FString::Printf(TEXT("GroupComp%d"), i));
		c->SetupAttachment(RootComponent);
		PipeGroup.Add(c);
	}

}

// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

