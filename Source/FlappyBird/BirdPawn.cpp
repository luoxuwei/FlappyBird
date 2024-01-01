// Fill out your copyright notice in the Description page of Project Settings.


#include "BirdPawn.h"
#include <PaperFlipbookComponent.h>
#include <Camera/CameraComponent.h>
#include <UObject/ConstructorHelpers.h>
#include <PaperFlipbook.h>
#include "PipeActor.h"
#include <Kismet/GameplayStatics.h>
#include "FlappyBirdGameModeBase.h"
#include <Curves/CurveFloat.h>

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

	CurrentState = EBirdState::EBS_Idle;

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
	FlyCurve = LoadObject<UCurveFloat>(nullptr, TEXT("CurveFloat'/Game/FlappyBird/Data/Curves/CV_BirdFly.CV_BirdFly'"));
}

// Called every frame
void ABirdPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateFace(DeltaTime);
	UpdateFly(DeltaTime);
}

void ABirdPawn::OnComponentBeginOverlap(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Log, TEXT("OnComponentBeginOverlap"));
	if (CurrentState == EBirdState::EBS_Dead || CurrentState == EBirdState::EBS_Idle) {
		return;
	}
	if (Cast<APipeActor>(OtherActor)) {
		ChangeState(EBirdState::EBS_Drop);
		if (AFlappyBirdGameModeBase *Gm = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			Gm->ChangeBirdGameState(EBirdGameState::EBGS_BirdDrop);
		}
	}
	else {
		ChangeState(EBirdState::EBS_Dead);
		if (AFlappyBirdGameModeBase* Gm = Cast<AFlappyBirdGameModeBase>(UGameplayStatics::GetGameMode(this)))
		{
			Gm->ChangeBirdGameState(EBirdGameState::EBGS_GameOver);
		}

	}
}

void ABirdPawn::DoFly() {
	UE_LOG(LogTemp, Log, TEXT("DoPLay"));
	if (CurrentState != EBirdState::EBS_Fly) return;
	
	BirdRenderComponent->SetAllPhysicsLinearVelocity(FVector::ZeroVector);
	BirdRenderComponent->AddImpulse(FVector::UpVector * 500, NAME_None, true);
}

void ABirdPawn::UpdateFace(float DeltaTime)
{
	if (CurrentState == EBirdState::EBS_Fly || CurrentState == EBirdState::EBS_Drop)
	{
		FVector Velocity = BirdRenderComponent->GetPhysicsLinearVelocity();
		float PitchValue = Velocity.Z * 15 * DeltaTime;
		BirdRenderComponent->SetRelativeRotation(FRotator(PitchValue, 0, 0));
	}
}

void ABirdPawn::UpdateFly(float DeltaTime)
{
	float MinTime, MaxTime;
	FlyCurve->GetTimeRange(MinTime, MaxTime);

	if ((CurveTick += DeltaTime) > MaxTime) {
		CurveTick = MinTime;
	}

	float value = FlyCurve->GetFloatValue(CurveTick);
	BirdRenderComponent->SetRelativeLocation(FVector(0, 0, value * 50));
}

// Called to bind functionality to input
void ABirdPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp, Log, TEXT("SetupPlayerInputComponent"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(TEXT("DoFly"), IE_Pressed, this, &ABirdPawn::DoFly);

}

void ABirdPawn::ChangeState(EBirdState State)
{
	if (CurrentState == State) return;
	switch (State)
	{
	case EBirdState::EBS_Idle:
		BirdRenderComponent->SetRelativeLocation(FVector::ZeroVector);
		BirdRenderComponent->SetRelativeRotation(FRotator::ZeroRotator);
		break;
	case EBirdState::EBS_Fly:
		BirdRenderComponent->SetSimulatePhysics(true);
		break;
	case EBirdState::EBS_Drop:
		break;
	case EBirdState::EBS_Dead:
		BirdRenderComponent->SetSimulatePhysics(false);
		break;
	default:
		break;
	}
	CurrentState = State;
}

