// Fill out your copyright notice in the Description page of Project Settings.


#include "Obtacle.h"
#include "SnakeBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Generation.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextRenderComponent.h"
// Sets default values
AObtacle::AObtacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LifeTimeTextComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("LifeTimeTextComponent"));
	LifeTimeTextComponent->AttachToComponent(nullptr, FAttachmentTransformRules::KeepRelativeTransform);
	LifeTimeTextComponent->SetHorizontalAlignment(EHTA_Center);
	LifeTimeTextComponent->SetWorldSize(25); // Регулируйте размер текста по необходимости

	// Смещение текста, чтобы он был над препятствием
	 // Регулируйте по необходимости

	LifeTimeTextComponent->SetWorldRotation(FRotator(-90.0f, 0, 0));
}



// Called when the game starts or when spawned
void AObtacle::BeginPlay()
{
	Super::BeginPlay();
	CurrentLifeTime = LifeTimeOfObtacle;

	GetWorldTimerManager().SetTimer(LifeTimeTimerHandle, this, &AObtacle ::LifeTimeTick, 1, true);

	UpdateLifeTimeText();
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
		GetWorldTimerManager().ClearTimer(LifeTimeTimerHandle);
		this->Destroy();
	}
	
	
}

void AObtacle::UpdateLifeTimeText()
{
	if (LifeTimeTextComponent)
	{
		LifeTimeTextComponent->SetText(FText::AsNumber(static_cast<int32>(CurrentLifeTime)));
	}
}

void AObtacle::LifeTimeTick()
{
	if (CurrentLifeTime > 0)
	{
		CurrentLifeTime -= 1;
		UpdateLifeTimeText();
	}
	else
	{
		OnDelayCompleted();
	}
}

