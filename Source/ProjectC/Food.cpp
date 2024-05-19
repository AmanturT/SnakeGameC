// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "SnakeBase.h"

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
					points += 1;
					this->Destroy();
					break;
				case 2:
					Snake->AddSnakeElement(2);
					points += 2;
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

