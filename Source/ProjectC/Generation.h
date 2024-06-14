// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generation.generated.h"

class AObtacle;
class ABaseMapSegment;
class ABasicMap;
class AFinalMap;
class ASnakeBase;
UCLASS()
class PROJECTC_API AGeneration : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneration();

	TArray<AObtacle*> SingleObtacles;
	TArray<AObtacle*> Structures;
	

	UPROPERTY(EditDefaultsOnly)
	int countOfSingleObtacles;

	UPROPERTY(EditDefaultsOnly)
	int countOfStructures;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABasicMap> BasicMapClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AFinalMap> FinalMapClass;

	ABaseMapSegment* CurrentMapSegment;
	ASnakeBase* Snake; // ��������� �� ����
	
	UPROPERTY(EditAnywhere)
	float MapSegmentLength = 2000.0f; // ����� �������� �����
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void GetActortFromFolder(const FString& WhichFolder,TArray<AObtacle*>& OutClasses);

	void GenerateObtacles(TArray<AObtacle*> ArrayOfObtacles, int count);

	void SpawnNewMapSegment(FVector SpawnLocation);

	void CheckSnakePosition();
};
