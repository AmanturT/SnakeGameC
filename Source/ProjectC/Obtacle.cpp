// Fill out your copyright notice in the Description page of Project Settings.


#include "Obtacle.h"
#include "SnakeBase.h"
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

