// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PipeActor.generated.h"
class USceneComponent;

UCLASS()
class FLAPPYBIRD_API APipeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APipeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float RandPipeGroupOffsetZ();
	void UpdateMove(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ResetPipePosition();
protected:
	UPROPERTY()
	TArray<USceneComponent*> PipeGroup;

	int32 MoveSpeed;
	float PipeInterval;
};
