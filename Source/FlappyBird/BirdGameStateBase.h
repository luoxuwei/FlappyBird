// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BirdGameStateBase.generated.h"
class USoundWave;

/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API ABirdGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:
	void AddScore();
	int32 GetScore() { return Score; }
	void ResetScore() { Score = 0; }
private:
	int32 Score;
	UPROPERTY()
	USoundWave* CoinSound;
};
