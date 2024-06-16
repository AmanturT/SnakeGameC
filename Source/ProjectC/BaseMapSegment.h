// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseMapSegment.generated.h"

UCLASS()
class PROJECTC_API ABaseMapSegment : public AActor
{
	GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABaseMapSegment();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Map Segment")
    float SegmentLength; // Общая длина сегмента карты
    // Static Mesh Component to represent the map segment
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComponent;
    // Общие функции, которые могут быть переопределены в производных классах
    virtual void InitializeSegment();
};
