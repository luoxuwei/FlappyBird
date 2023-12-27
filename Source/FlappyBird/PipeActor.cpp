// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"
#include <Components/SceneComponent.h>
#include <PaperSprite.h>
#include <PaperSpriteComponent.h>

// Sets default values
APipeActor::APipeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));

	ConstructorHelpers::FObjectFinder<UPaperSprite> UpSpriteObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipes/pipe_up_Sprite.pipe_up_Sprite'"));
	ConstructorHelpers::FObjectFinder<UPaperSprite> DownSpriteObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/Pipes/pipe_down_Sprite.pipe_down_Sprite'"));

	for (size_t i = 0; i < 3; i++)
	{
		USceneComponent *c = CreateDefaultSubobject<USceneComponent>(*FString::Printf(TEXT("GroupComp%d"), i));
		c->SetupAttachment(RootComponent);
		PipeGroup.Add(c);
		UPaperSpriteComponent* SpriteUp = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("Group%dPipeUp"), i));
		UPaperSpriteComponent* SpriteDown = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("Group%dPipeDown"), i));
		SpriteUp->SetupAttachment(c);
		SpriteUp->SetSprite(UpSpriteObj.Object);
		SpriteDown->SetupAttachment(c);
		SpriteDown->SetSprite(DownSpriteObj.Object);
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

