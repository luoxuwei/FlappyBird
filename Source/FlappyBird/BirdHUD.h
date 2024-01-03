// Fill out your copyright noticein the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BirdHUD.generated.h"
class UTexture;
/**
 * 
 */
UCLASS()
class FLAPPYBIRD_API ABirdHUD : public AHUD
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	void DrawGameScoreNunber();
	void DrawScreenFade();

public:
	void StartFade();
	
private:
	UTexture* NumberTexture;
	UPROPERTY()
	TArray<UTexture*> NumberTextureArray;
	float FadeAlpha;
	float FadeSpeed;
	bool bFade;
};
