// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementBase.h"
#include "Components/StaticMeshComponent.h"
#include "SnakeBase.h"
// Sets default values
ASnakeElementBase::ASnakeElementBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);


	AdditionalMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AdditionalMeshComponent"));
	AdditionalMeshComponent->SetupAttachment(MeshComponent);
	AdditionalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/Meshes/SnakeHat/SimpleCrown.SimpleCrown'"));
	if (MeshAsset.Succeeded())
	{
		AdditionalMesh = MeshAsset.Object;
	}
}

// Called when the game starts or when spawned
void ASnakeElementBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASnakeElementBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASnakeElementBase::SetFirstElementType_Implementation()
{
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ASnakeElementBase::HandleBeginOverlap);
	UE_LOG(LogTemp, Error, TEXT("Func is work"));
	if (AdditionalMesh)
	{
		AdditionalMeshComponent->SetStaticMesh(AdditionalMesh);
		AdditionalMeshComponent->SetRelativeLocation(FVector(0, 0, 100)); 
		AdditionalMeshComponent->SetRelativeScale3D(FVector(40, 40, 40));
		UE_LOG(LogTemp, Error, TEXT("Mesh not null"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Mesh null"));
	}
}

void ASnakeElementBase::Interact(AActor* Interactor, bool bIsHead)
{
	auto Snake = Cast<ASnakeBase>(Interactor);
	if (IsValid(Snake))
	{
		Snake->Destroy();
	}
}

void ASnakeElementBase::HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
										   AActor* OtherActor,
										   UPrimitiveComponent* OtherComp, 
										   int32 OtherBodyIndex, 
										   bool bFromSweep,
										   const FHitResult &SweepResult)
{
	if (IsValid(SnakeOwner))
	{
		SnakeOwner->SnakeElementOverlapped(this,OtherActor);
	}
}

void ASnakeElementBase::ToggleCollision()
{
	if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}




