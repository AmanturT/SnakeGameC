// Fill out your copyright notice in the Description page of Project Settings.


#include "Obtacle.h"
#include "SnakeBase.h"
#include "Kismet/KismetSystemLibrary.h"
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
			Snake->Destroy();
		}
	}
}


void AObtacle::OnDelayCompleted()
{
	UE_LOG(LogTemp, Warning, TEXT("Delay completed"));
	if (IsObtacleImmortal == true)
	{
		UE_LOG(LogTemp,Warning,TEXT("THIS OBJECT IS IMMORTAL"))
	}
	else {
		this->Destroy();
	}
	
}

