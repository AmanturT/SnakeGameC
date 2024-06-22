// Fill out your copyright notice in the Description page of Project Settings.


#include "Obtacle.h"
#include "SnakeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Generation.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AObtacle::AObtacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void AObtacle::BeginPlay()
{
	Super::BeginPlay();
	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = FName("OnDelayCompleted");
	LatentInfo.Linkage = 0;
	LatentInfo.UUID = FMath::Rand();
	UKismetSystemLibrary::Delay(this, LifeTimeOfObtacle, LatentInfo);
}

// Called every frame
void AObtacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObtacle::Interact(AActor* Interactor, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactor);
		if (IsValid(Snake))
		{
			if (IsObtacleGameField)
			{
				GenerationClass = Cast<AGeneration>(UGameplayStatics::GetActorOfClass(GetWorld(), AGeneration::StaticClass()));
				if (GenerationClass)
				{
					GenerationClass->CheckSnakeLocation();
					this->Destroy();
				}
				
			}
			else
			{
				if (Snake->IsInvincibleForObtacles == false)
					{
						Snake->Destroy();
					}
				else
					{
						if (IsObtacleBarrier)
							{
								Snake->Destroy();
							}
				
					}
			}
			
		}
	}
}


void AObtacle::OnDelayCompleted()
{
	
	if (IsObtacleImmortal == false)
	{
		this->Destroy();
	}
	
	
}

