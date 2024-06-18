// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawnBase.h"
#include "Camera/CameraComponent.h"
#include "SnakeBase.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ShowStamina.h"
// Sets default values
APlayerPawnBase::APlayerPawnBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CameraPawn = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraPawn"));
	RootComponent = CameraPawn;
	IsBoosting = false;
}

// Called when the game starts or when spawned
void APlayerPawnBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(FRotator(-90, 0, 0));
	CurrentBoostCount = TotalBoostCount;
	
}

// Called every frame
void APlayerPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsBoosting)
	{
		CurrentBoostCount -= 1;
		if (CurrentBoostCount <= 0)
		{
			OnBoostReleased();
			
		}
	
	}
	else
	{
		if (CurrentBoostCount < TotalBoostCount)
		{
			CurrentBoostCount += 1;
			
		}
		
		
	}
	UpdateStaminaProgressBar();
}

// Called to bind functionality to input
void APlayerPawnBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &APlayerPawnBase::HandlePlayerVerticalInput);

	PlayerInputComponent->BindAxis("Horizontal", this, &APlayerPawnBase::HandlePlayerHorizontalInput);

	PlayerInputComponent->BindAction("StartGame", IE_Pressed, this, &APlayerPawnBase::StartGame);
	PlayerInputComponent->BindAction("StopGame", IE_Pressed, this, &APlayerPawnBase::StopGame);

	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &APlayerPawnBase::OnBoostPressed);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &APlayerPawnBase::OnBoostReleased);
}

void APlayerPawnBase::CreateSnakeActor()
{
	SnakeActor = GetWorld()->SpawnActor<ASnakeBase>(SnakeActorClass, FTransform());
	ShowStaminaProgressBar();
}

void APlayerPawnBase::HandlePlayerVerticalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::DOWN)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::UP;
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::UP)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::DOWN;
		}
	}
}

void APlayerPawnBase::HandlePlayerHorizontalInput(float value)
{
	if (IsValid(SnakeActor))
	{
		if (value > 0 && SnakeActor->LastMoveDirection != EMovementDirection::LEFT)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::RIGHT;
		}
		else if (value < 0 && SnakeActor->LastMoveDirection != EMovementDirection::RIGHT)
		{
			SnakeActor->LastMoveDirection = EMovementDirection::LEFT;
		}
	}
}

void APlayerPawnBase::StartGame()
{   

	FActorSpawnParameters SpawnParams;
	if (!IsGameStarted)
	{
		CreateSnakeActor();
		IsGameStarted = true;
	}
	else {
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1);
		UE_LOG(LogTemp, Error, TEXT("Input Working Start2"))
	}
}

void APlayerPawnBase::StopGame()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(),0 );
	UE_LOG(LogTemp, Error, TEXT("Input Working Stop"))
}

void APlayerPawnBase::OnBoostPressed()
{
	IsBoosting = true;
	if (CurrentBoostCount != 0)
	{
		SnakeActor->SetActorTickInterval(SnakeActor->MovementSpeed * 0.5);
		
	
	}

}

void APlayerPawnBase::OnBoostReleased()
{
	IsBoosting = false;
	SnakeActor->SetActorTickInterval(SnakeActor->MovementSpeed);
	if (CurrentBoostCount < TotalBoostCount)
	{
		

	}
	
}

void APlayerPawnBase::ShowStaminaProgressBar()
{
	StaminaProgressBar = CreateWidget<UShowStamina>(GetWorld(), StaminaWidgerClass);
	if (StaminaProgressBar)
	{
		StaminaProgressBar->AddToViewport(1);
	}
}

void APlayerPawnBase::UpdateStaminaProgressBar()
{
	if (StaminaProgressBar)
	{
		if (TotalBoostCount != 0)
		{
			float Progress = static_cast<float>(CurrentBoostCount) / static_cast<float>(TotalBoostCount);
			float RoundedProgress = FMath::RoundToFloat(Progress * 100.0f) / 100.0f;
			StaminaProgressBar->SetStaminaProgressBar(RoundedProgress);

			
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("TotalBoostCount is zero"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StaminaProgressBar is nullptr"));
	}
}

