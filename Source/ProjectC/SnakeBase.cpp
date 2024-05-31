// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"
#include "SnakeElementsShow.h"
#include "Blueprint/UserWidget.h"

// Sets dault values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	LastMoveDirection = EMovementDirection::DOWN;
	static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/Blueprints/GUI/SnakeElementsShowWidget.SnakeElementsShowWidget_C"));

	if (WidgetClassFinder.Succeeded())
	{
		WidgetClass = WidgetClassFinder.Class;
	}
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(5);
	SetWidgetText();
	

}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; i++)
	{
		FVector NewLocation;
		if (SnakeElements.Num() > 0)
		{
			ASnakeElementBase* LastElement = SnakeElements[SnakeElements.Num()- 1];
			NewLocation = LastElement->GetActorLocation() + FVector(ElementSize, 0, 0);
		}

		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementBase, NewTransform);
		int32 ElemIndex = SnakeElements.Add(NewSnakeElem);
		NewSnakeElem->SnakeOwner = this;


		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();
			
		}
	
	}
	SetWidgetText();
}

void ASnakeBase::Move()
{
	
	FVector MovementVector(ForceInitToZero);


	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += ElementSize;
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= ElementSize;
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += ElementSize;
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= ElementSize;
		break;
	}

	//AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PreviousElement = SnakeElements[i - 1];
		FVector PreviousLocation = PreviousElement->GetActorLocation();
		CurrentElement->SetActorLocation(PreviousLocation);

	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::SnakeElementOverlapped(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractableInterface = Cast<IInteractable>(Other);
		if (InteractableInterface)
		{
			InteractableInterface->Interact(this,bIsFirst);
			
		}
	}
}

void ASnakeBase::RemoveSnakeElement(int NumElementsToRemove)
{
	if (SnakeElements.Num() >= NumElementsToRemove)
	{
		
		for (int i = 0; i < NumElementsToRemove; ++i)
		{
			ASnakeElementBase* LastElement = SnakeElements.Last();
			SnakeElements.RemoveAt(SnakeElements.Num() - 1);
			LastElement->Destroy();
		}
	}
	else
	{
		this->Destroy();
	}
	SetWidgetText();
}

void ASnakeBase::SetWidgetText()
{
	if (CurrentSnakeElementsWidget != nullptr)
	{
		CurrentSnakeElementsWidget->RemoveFromParent();
		CurrentSnakeElementsWidget = nullptr;
	}

	
	CurrentSnakeElementsWidget = CreateWidget<USnakeElementsShow>(GetWorld(), WidgetClass);
	if (CurrentSnakeElementsWidget != nullptr)
	{
		CurrentSnakeElementsWidget->AddToViewport(1); 
		CurrentSnakeElementsWidget->UpdateElementCount(SnakeElements.Num());
	}
	

}

