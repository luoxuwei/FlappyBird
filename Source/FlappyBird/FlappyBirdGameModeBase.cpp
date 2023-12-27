// Copyright Epic Games, Inc. All Rights Reserved.


#include "FlappyBirdGameModeBase.h"
#include "BirdPawn.h"
#include "BgActor.h"
#include "LandActor.h"


AFlappyBirdGameModeBase::AFlappyBirdGameModeBase() {
	DefaultPawnClass = ABirdPawn::StaticClass();
}

void AFlappyBirdGameModeBase::BeginPlay() {
	Super::BeginPlay();
	BgActor = GetWorld()->SpawnActor<ABgActor>();
	BgActor->SetActorLocation(FVector(0, -100, 0));
	LandActor = GetWorld()->SpawnActor<ALandActor>();
	LandActor->SetActorLocation(FVector(0, 0, -200));
}