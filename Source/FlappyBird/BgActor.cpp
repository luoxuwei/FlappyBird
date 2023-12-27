// Fill out your copyright notice in the Description page of Project Settings.


#include "BgActor.h"
#include <PaperSpriteComponent.h>
#include <PaperSprite.h>

// Sets default values
ABgActor::ABgActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	BgRenderComp = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("BgRenderComp"));
	SetRootComponent(BgRenderComp);

}

void ABgActor::RandomBgSprite() {
	FString path = FMath::RandBool()? TEXT("PaperSprite'/Game/FlappyBird/Textures/bg/bg_day_Sprite.bg_day_Sprite'")
		:TEXT("PaperSprite'/Game/FlappyBird/Textures/bg/bg_night_Sprite.bg_night_Sprite'");


	UPaperSprite* BgSprite = LoadObject<UPaperSprite>(nullptr, *path);
	BgRenderComp->SetSprite(BgSprite);
}

// Called when the game starts or when spawned
void ABgActor::BeginPlay()
{
	Super::BeginPlay();
	RandomBgSprite();

}
 
// Called every frame
void ABgActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

