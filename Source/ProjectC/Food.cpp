// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFood::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			switch (id)
			{
				case 1:
					Snake->AddSnakeElement(1);
				
					
					this->MoveFood();
					break;
				case 2:
					Snake->AddSnakeElement(2);
		
					this->Destroy();
					break;
				case 3:
					Snake->RemoveSnakeElement(1);
					this->Destroy();
					break;
				case 4:
					Snake->RemoveSnakeElement(2);
					this->Destroy();
					break;
			}
			;
		}
	}
}



void AFood::MoveFood()
{
	int iterator = 0;
	bool flag = false;
	FVector NewCoords;

	const float radius = 32.0f; 
	ETraceTypeQuery sphereTraceQuery = ETraceTypeQuery::TraceTypeQuery1;
	const TArray<AActor*> ActorsToIgnore;
	const float drawTime = 5.0f;
	UWorld* World = GetWorld();
	while (iterator != 150 || flag == false)
	{
		
		NewCoords = FVector(FMath::RandRange(-200,200), FMath::RandRange(-200, 200), 20);
		TArray<FHitResult> HitResults; 

		UKismetSystemLibrary::SphereTraceMulti(World, NewCoords, NewCoords, radius, sphereTraceQuery, false,
			ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResults, true,
			FLinearColor::Green, FLinearColor::Red, drawTime);

		if (HitResults.Num() == 0) 
		{
			this->SetActorLocation(NewCoords);
			flag = true;
		}

		iterator++; 
	}
}

