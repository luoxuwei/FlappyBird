// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdGameStateBase.h"
#include <Sound/SoundWave.h>
#include <Kismet/GameplayStatics.h>

void ABirdGameStateBase::AddScore()
{
	Score++;
	if (!CoinSound) {
		CoinSound = LoadObject<USoundWave>(nullptr, TEXT("SoundWave'/Game/FlappyBird/sounds/coin.coin'"));
	}
	UGameplayStatics::PlaySound2D(this, CoinSound);
}
