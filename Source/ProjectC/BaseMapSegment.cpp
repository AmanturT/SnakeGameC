// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseMapSegment.h"

// Sets default values
ABaseMapSegment::ABaseMapSegment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
}

// Called when the game starts or when spawned
void ABaseMapSegment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseMapSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseMapSegment::InitializeSegment()
{
	// Define the size of the segment
	FVector SegmentSize = FVector(7000, 7000, 1);

	// Set the scale of the mesh component
	MeshComponent->SetWorldScale3D(SegmentSize);
	UE_LOG(LogTemp,Error,TEXT("BaseMapSegment initialized"))
}

