// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdGameModeBase.generated.h"

class ABgActor;
class ALandActor;
class APipeActor;
/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API AFlappyBirdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		AFlappyBirdGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ABgActor* BgActor;
	UPROPERTY()
	ALandActor* LandActor;
	UPROPERTY()
	APipeActor* PipeActor;
};
