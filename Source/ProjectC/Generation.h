// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generation.generated.h"


class AFood;
class AObtacle;
class ASnakeBase;
UCLASS()
class PROJECTC_API AGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneration();

	TArray<UObject*> SingleObtacles;

	TArray<UObject*> GameFieldSegments;

	UPROPERTY(EditDefaultsOnly)
	int countOfSingleObtacles;

	


	FVector LastSpawnedSegmentEnd;
	FVector SegmentSize = FVector(2000, 2000, 0);

	ASnakeBase* SnakeBaseClass;

	AFood* FoodClass;

	UPROPERTY(EditDefaultsOnly)
	int CountOfGeneratingFood;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void GetActortFromFolder(const FString& WhichFolder,TArray<UObject*>& OutClasses);

	void GenerateObtacles(TArray<UObject*> ArrayOfObtacles, int count);

	void SpawnNewSegment(FVector SpawnLocation);

	void CheckSnakeLocation();

	void FindSnake();

};
