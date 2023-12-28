// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"
#include "BirdPawn.h"
#include "BgActor.h"
#include "LandActor.h"
#include "PipeActor.h"
#include <Kismet/GameplayStatics.h>


AFlappyBirdGameModeBase::AFlappyBirdGameModeBase() {
	DefaultPawnClass = ABirdPawn::StaticClass();
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
		BeginGame();
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
