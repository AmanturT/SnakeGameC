// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Interactable.h"
#include "Food.generated.h"

class AGeneration;
UCLASS()

class PROJECTC_API AFood : public AActor, public IInteractable
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	int id;


	UPROPERTY(EditDefaultsOnly)
	int MaxRespawns;

	UPROPERTY(EditDefaultsOnly)
	float HungerTime;

	UPROPERTY(EditDefaultsOnly)
	int CountOfGeneratingFood;

	UPROPERTY(EditDefaultsOnly)
	bool IsGeneratingBlueprint;

	
	AGeneration* GenerationClass;
	
	TArray<AFood*> FoodLoadedArray;


	UPROPERTY(EditDefaultsOnly)
	float LifeTimeOfFood;

	float CurrentLifeTime;
	FTimerHandle LifeTimeTimerHandle;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* LifeTimeTextComponent;
public:	
	// Sets default values for this actor's properties
	AFood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	

	void GetActortFromFolder(const FString& WhichFolder, TArray<AFood*>& OutClasses);

	void GenerateFood(AFood* WhichFoodType);

	AFood* GetRandomFoodType();
	//Проверка не находится ли будущая еда в месте спавна змейки
	bool IsNewCoordsInSnakeSpawn(float pointX, float pointY, float sideLength);

	UFUNCTION()
	void DestroyFood();
	void UpdateLifeTimeText();
	void LifeTimeTick();
};
