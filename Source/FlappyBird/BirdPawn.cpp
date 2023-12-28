// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include <PaperFlipbookComponent.h>
#include <Camera/CameraComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <PaperFlipbook.h>

// Sets default values
ABirdPawn::ABirdPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootCom"));
	BirdRenderComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("BirdRenderComp"));
	BirdRenderComponent->SetupAttachment(RootComponent);

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCamera->SetupAttachment(RootComponent);
	PlayerCamera->SetRelativeRotation(FRotator(0, -90, 0));
	PlayerCamera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	PlayerCamera->SetRelativeLocation(FVector(0, 100, 0));
	PlayerCamera->SetOrthoWidth(1000.f);

	ConstructorHelpers::FObjectFinder<UPaperFlipbook> BirdbookObj(TEXT("PaperFlipbook'/Game/FlappyBird/Anima/Birds/PF_RedBird.PF_RedBird'"));
	BirdRenderComponent->SetFlipbook(BirdbookObj.Object);
	BirdRenderComponent->SetCollisionProfileName(TEXT("OverlapAll"));
	BirdRenderComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BirdRenderComponent->OnComponentBeginOverlap.AddDynamic(this, &ABirdPawn::OnComponentBeginOverlap);

}

// Called when the game starts or when spawned
void ABirdPawn::BeginPlay()
{
	Super::BeginPlay();
	auto body = BirdRenderComponent->GetBodyInstance();
	if (body) {
		body->bLockXTranslation = true;
		body->bLockYTranslation = true;
		body->bLockXRotation = true;
		body->bLockZRotation = true;
		body->CreateDOFLock();
	}
}

// Called every frame
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABirdPawn::OnComponentBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("OnComponentBeginOverlap"));
}

void ABirdPawn::DoFly() {
	UE_LOG(LogTemp, Log, TEXT("DoPLay"));
	BirdRenderComponent->SetSimulatePhysics(true);
	BirdRenderComponent->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	BirdRenderComponent->AddImpulse(FVector::UpVector * 500, NAME_None, true);
}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Log, TEXT("SetupPlayerInputComponent"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("DoFly"), IE_Pressed, this, &ABirdPawn::DoFly);

}

