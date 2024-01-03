// Fill out your copyright notice in the Description page of Project Settings.


#include "PipeActor.h"
#include <Components/SceneComponent.h>
#include <PaperSprite.h>
#include <PaperSpriteComponent.h>
#include <Kismet/GameplayStatics.h>
#include "BirdGameStateBase.h"

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
		PipGroupUsed.Add(false);
		UPaperSpriteComponent* SpriteUp = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("Group%dPipeUp"), i));
		UPaperSpriteComponent* SpriteDown = CreateDefaultSubobject<UPaperSpriteComponent>(*FString::Printf(TEXT("Group%dPipeDown"), i));
		SpriteUp->SetupAttachment(c);
		SpriteUp->SetSprite(DownSpriteObj.Object);
		SpriteDown->SetupAttachment(c);
		SpriteDown->SetSprite(UpSpriteObj.Object);

		SpriteUp->SetRelativeLocation(FVector(0, 0, 200));
		SpriteDown->SetRelativeLocation(FVector(0, 0, -200));

	}

	MoveSpeed = 0;
	PipeInterval = 160;

}

// Called when the game starts or when spawned
void APipeActor::BeginPlay()
{
	Super::BeginPlay();
	ResetPipePosition();
	
}

float APipeActor::RandPipeGroupOffsetZ()
{
	return FMath::RandRange(-80, 150);
}

void APipeActor::UpdateMove(float DeltaTime)
{
	for (int32 i = 0; i < 3; i++)
	{
		PipeGroup[i]->AddRelativeLocation(FVector::ForwardVector * -1 * MoveSpeed * DeltaTime);
		if (PipeGroup[i]->GetRelativeTransform().GetLocation().X < -200) {
			int32 FollowSize = (i == 0) ? 2 : i - 1;

			float x = (PipeGroup[FollowSize]->GetRelativeTransform().GetLocation() + FVector::ForwardVector * PipeInterval).X;
			PipeGroup[i]->SetRelativeLocation(FVector(x, 0, RandPipeGroupOffsetZ()));
			PipGroupUsed[i] = false;
		}

		if (!PipGroupUsed[i] && PipeGroup[i]->GetRelativeTransform().GetLocation().X < -150) {
			AGameStateBase* Gs = UGameplayStatics::GetGameState(this);
			ABirdGameStateBase* BirdGs = Cast<ABirdGameStateBase>(Gs);
			if (BirdGs) {
				BirdGs->AddScore();
			}
			PipGroupUsed[i] = true;
		}
	}
}

// Called every frame
void APipeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMove(DeltaTime);

}

void APipeActor::ResetPipePosition()
{
	for (size_t i = 0; i < 3; i++)
	{
		PipeGroup[i]->SetRelativeLocation(FVector(200 + i * PipeInterval, 0, RandPipeGroupOffsetZ()));
	}

}

void APipeActor::SetMoveSpeed(float Speed /*= 100*/)
{
	MoveSpeed = Speed;
}

