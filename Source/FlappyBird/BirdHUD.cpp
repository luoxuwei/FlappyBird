// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdHUD.h"
#include <Engine/Texture.h>
#include <Kismet/GameplayStatics.h>
#include "BirdGameStateBase.h"
#include <Engine/Canvas.h>

void ABirdHUD::BeginPlay()
{
	Super::BeginPlay();
	NumberTexture = LoadObject<UTexture>(nullptr, TEXT("Texture2D'/Game/FlappyBird/Textures/numbers/font_048.font_048'"));
	for (int i = 48; i < 58; i++)
	{
		NumberTextureArray.Add(LoadObject<UTexture>(nullptr, *FString::Printf(TEXT("Texture2D'/Game/FlappyBird/Textures/numbers/font_0%d.font_0%d'"), i, i)));
	}
}

void ABirdHUD::DrawHUD()
{
	Super::DrawHUD();
	DrawGameScoreNunber();

}

void ABirdHUD::DrawGameScoreNunber()
{
	if (ABirdGameStateBase* Gs = Cast<ABirdGameStateBase>(UGameplayStatics::GetGameState(this)))
	{
		int32 score = Gs->GetScore() + 10;
		TArray<int32> nums;
		while (score)
		{
			nums.Add(score % 10);
			score = score / 10;

		}
		
		float CenterX = Canvas->ClipX / 2;
		if (!nums.Num()) {
			DrawTextureSimple(NumberTextureArray[0], CenterX, 50);
		}
		else {
			for (int32 i = 0, len = nums.Num(); i < len; ++i)
			{
				float DrawX = (len * 24 + 2 *(len - 1)) / 2 + CenterX - 24;
				DrawTextureSimple(NumberTextureArray[nums[i]], DrawX - i * 50, 50);
			}
		}


	}
}
