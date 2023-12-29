// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdPawn.generated.h"
class UPaperFlipbookComponent;
class UCameraComponent;

UENUM(BlueprintType)
enum class EBirdState : uint8
{
	EBS_Idle,
	EBS_Fly,
	EBS_Drop,
	EBS_Dead,
};

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
	void UpdateFace(float DeltaTime);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ChangeState(EBirdState State);

protected:
	UPROPERTY(VisibleAnywhere)
	UPaperFlipbookComponent* BirdRenderComponent;
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* PlayerCamera;
    UPROPERTY(VisibleAnywhere)
	EBirdState CurrentState;

};
