// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LandActor.generated.h"
class UPaperSpriteComponent;
class UStaticMeshComponent;

UCLASS()
class FLAPPYBIRD_API ALandActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALandActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void UpdateMove(float DeltaTime);
private:
	UPROPERTY()
	UPaperSpriteComponent* LandRenderComp0;
	UPROPERTY()
	UPaperSpriteComponent* LandRenderComp1;
	int32 MoveSpeed;
	UPROPERTY()
	UStaticMeshComponent* LandMeshRender;
};
