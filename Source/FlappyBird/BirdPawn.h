// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdPawn.generated.h"
class UPaperFlipbookComponent;
class UCameraComponent;

UCLASS()
class FLAPPYBIRD_API ABirdPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DoFly();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* BirdRenderComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamera;

};
