// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
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
				
					Snake->Hunger(HungerTime);
					this->MoveFood();
					break;
				case 2:
					Snake->AddSnakeElement(2);
					Snake->Hunger(HungerTime);
					this->MoveFood();
					break;
				case 3:
					Snake->RemoveSnakeElement(1);
					Snake->Hunger(HungerTime);
					this->MoveFood();
					break;
				case 4:
					Snake->RemoveSnakeElement(2);
					Snake->Hunger(HungerTime);
					this->MoveFood();
					break;
				case 5:
					Snake->SetActorTickInterval(Snake->MovementSpeed * 0.7);
					
					Snake->Hunger(HungerTime);
					this->MoveFood();
					
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
	ASnakeBase* SnakeBase = Cast<ASnakeBase>(UGameplayStatics::GetActorOfClass(World, ASnakeBase::StaticClass()));
	FVector SnakeBaseLocation;
	FBox FoodBoundingBox = GetComponentsBoundingBox();
	if (SnakeBase)
	{
		SnakeBaseLocation = SnakeBase->GetActorLocation();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SnakeBase is nullptr"));
	}
	
	if (MaxRespawns < 3)
	{
		while (iterator < 150  && !flag ) 
			{
				NewCoords = FVector(FMath::RandRange(-1000, 1000), FMath::RandRange(-1000,1000), SnakeBaseLocation.Z + FoodBoundingBox.GetSize().Z / 4);
				TArray<FHitResult> HitResults;

				UKismetSystemLibrary::SphereTraceMulti(World, NewCoords, NewCoords, radius, sphereTraceQuery, false,
					ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResults, true,
					FLinearColor::Green, FLinearColor::Red, drawTime);

				if (HitResults.Num() == 0)
				{
					this->SetActorLocation(NewCoords);
					flag = true;
				}
				else
				{
					UE_LOG(LogTemp, Log, TEXT("SnakeBase Z Coordinate: %f"), SnakeBaseLocation.Z);
				}
				iterator++;
		
			}
		MaxRespawns += 1;
	}
	else
	{
		this->Destroy();
	}
	

	
}
