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
    float SegmentLength; // ����� ����� �������� �����
    // Static Mesh Component to represent the map segment
    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* MeshComponent;
    // ����� �������, ������� ����� ���� �������������� � ����������� �������
    virtual void InitializeSegment();
};
