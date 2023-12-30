// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FlappyBirdGameModeBase.generated.h"

class ABgActor;
class ALandActor;
class APipeActor;

UENUM(BlueprintType)
enum class EBirdGameState : uint8
{
	EBGS_Menu,
	EBGS_Gaming,
	EBGS_BirdDrop,
	EBGS_GameOver,
};

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

public:
	UFUNCTION(Exec)
	void ChangeGameState(int32 State);
	void BeginGame();
	void ChangeBirdGameState(EBirdGameState State);
	void StopSceneObject();

private:
	UPROPERTY()
	ABgActor* BgActor;
	UPROPERTY()
	ALandActor* LandActor;
	UPROPERTY()
	APipeActor* PipeActor;
	EBirdGameState CurrentState;
};
