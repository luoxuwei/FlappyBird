// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"
#include "BirdPawn.h"
#include "BgActor.h"
#include "LandActor.h"
#include "PipeActor.h"
#include <Kismet/GameplayStatics.h>
#include "BirdGameStateBase.h"


AFlappyBirdGameModeBase::AFlappyBirdGameModeBase() {
	DefaultPawnClass = ABirdPawn::StaticClass();
	GameStateClass = ABirdGameStateBase::StaticClass();
}

void AFlappyBirdGameModeBase::BeginPlay() {
	Super::BeginPlay();
	BgActor = GetWorld()->SpawnActor<ABgActor>();
	BgActor->SetActorLocation(FVector(0, -100, 0));
	LandActor = GetWorld()->SpawnActor<ALandActor>();
	LandActor->SetActorLocation(FVector(0, 2, -200));
	PipeActor = GetWorld()->SpawnActor<APipeActor>();
	PipeActor->SetActorLocation(FVector(0, 0, 0));
}

void AFlappyBirdGameModeBase::ChangeGameState(int32 State)
{
	if (0 == State) {
		ChangeBirdGameState(EBirdGameState::EBGS_Gaming); 
	}
	else if (1 == State) {
		ResetGame();
		ChangeBirdGameState(EBirdGameState::EBGS_Menu);
	}
}

void AFlappyBirdGameModeBase::BeginGame()
{
	PipeActor->SetMoveSpeed();
	APawn* Pawn = UGameplayStatics::GetPlayerPawn(this, 0);
	ABirdPawn* BirdPawn = Cast<ABirdPawn>(Pawn);
	if (BirdPawn) {
		BirdPawn->ChangeState(EBirdState::EBS_Fly);
	}   
}

void AFlappyBirdGameModeBase::ChangeBirdGameState(EBirdGameState State)
{
	switch (State)
	{
	case EBirdGameState::EBGS_Menu:
		break;
	case EBirdGameState::EBGS_Gaming:
		BeginGame();
		break;
	case EBirdGameState::EBGS_BirdDrop:
		StopSceneObject();
		break;
	case EBirdGameState::EBGS_GameOver:
		StopSceneObject();
		break;
	default:
		break;
	}
	CurrentState = State;
}

void AFlappyBirdGameModeBase::StopSceneObject()
{
	PipeActor->SetMoveSpeed(0);
	LandActor->SetMoveSpeed(0);
}

void AFlappyBirdGameModeBase::ResetGame()
{
	BgActor->RandomBgSprite();
	PipeActor->ResetPipePosition();
	if (ABirdPawn* Bp = Cast<ABirdPawn>(UGameplayStatics::GetPlayerPawn(this, 0))) {
		Bp->ChangeState(EBirdState::EBS_Idle);
	}
}
