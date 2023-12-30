// Fill out your copyright notice in the Description page of Project Settings.


#include "LandActor.h"
#include <PaperSpriteComponent.h>
#include <PaperSprite.h>
#include <UObject/ConstructorHelpers.h>
#include <Components/StaticMeshComponent.h>
#include <Engine/StaticMesh.h>
#include <Materials/Material.h>

// Sets default values
ALandActor::ALandActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootCom"));
 //   LandRenderComp0 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandRenderComp0"));
	//LandRenderComp0->SetupAttachment(RootComponent);
	//LandRenderComp1 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("LandRenderComp1"));
	//LandRenderComp1->SetupAttachment(RootComponent);

	//ConstructorHelpers::FObjectFinder<UPaperSprite> BirdbookObj(TEXT("PaperSprite'/Game/FlappyBird/Textures/bg/land_Sprite.land_Sprite'"));
	//LandRenderComp0->SetSprite(BirdbookObj.Object);
	//LandRenderComp1->SetSprite(BirdbookObj.Object);
	//LandRenderComp1->SetRelativeLocation(FVector(336, 0, 0));

	//MoveSpeed = 200;

	LandMeshRender = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LandMeshRender"));
	LandMeshRender->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> PlanMeshObj(TEXT("StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	LandMeshRender->SetStaticMesh(PlanMeshObj.Object);
	ConstructorHelpers::FObjectFinder<UMaterial> PlanMatObj(TEXT("Material'/Game/FlappyBird/Materials/M_LandSprite.M_LandSprite'"));
	LandMeshRender->SetMaterial(0, PlanMatObj.Object);

	LandMeshRender->SetRelativeRotation(FRotator(0, 0, 90));
	LandMeshRender->SetRelativeScale3D(FVector(3, 1, 1));

}

// Called when the game starts or when spawned
void ALandActor::BeginPlay()
{
	Super::BeginPlay();
	LandMeshRender->SetScalarParameterValueOnMaterials(TEXT("Speed"), 0.05);
}

void ALandActor::UpdateMove(float DeltaTime) {

	if (!LandRenderComp0 || !LandRenderComp1) {
		return;
	}

	LandRenderComp0->AddRelativeLocation(FVector::ForwardVector * -1 * MoveSpeed * DeltaTime);
	LandRenderComp1->AddRelativeLocation(FVector::ForwardVector * -1 * MoveSpeed * DeltaTime);

	if (LandRenderComp0->GetRelativeTransform().GetLocation().X < -336) {
		LandRenderComp0->SetRelativeLocation(LandRenderComp1->GetRelativeTransform().GetLocation() + FVector::ForwardVector * 336);
	}
	if (LandRenderComp1->GetRelativeTransform().GetLocation().X < -336) {
		LandRenderComp1->SetRelativeLocation(LandRenderComp0->GetRelativeTransform().GetLocation() + FVector::ForwardVector * 336);
	}

}


void ALandActor::SetMoveSpeed(float Speed)
{
	MoveSpeed = Speed;
	LandMeshRender->SetScalarParameterValueOnMaterials(TEXT("Speed"), MoveSpeed);

}

// Called every frame
void ALandActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateMove(DeltaTime);

}

