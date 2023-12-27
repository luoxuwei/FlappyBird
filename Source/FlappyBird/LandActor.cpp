// Fill out your copyright notice in the Description page of Project Settings.


#include "LandActor.h"
#include <PaperSpriteComponent.h>
#include <PaperSprite.h>
#include <UObject/ConstructorHelpers.h>

// Sets default values
ALandActor::ALandActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootCom"));
    LandRenderComp0 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandRenderComp0"));
	LandRenderComp0->SetupAttachment(RootComponent);
	LandRenderComp1 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandRenderComp1"));
	LandRenderComp1->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UPaperSprite> BirdbookObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/bg/land_Sprite.land_Sprite'"));
	LandRenderComp0->SetSprite(BirdbookObj.Object);
	LandRenderComp1->SetSprite(BirdbookObj.Object);
	LandRenderComp1->SetRelativeLocation(FVector(336, 0, 0));
}

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALandActor::UpdateMove(float DeltaTime) {

}

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

