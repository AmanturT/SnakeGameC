// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"


class UHungerWidget;
class ASnakeElementBase;
class USnakeElementsShow;
UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};


UCLASS()
class PROJECTC_API ASnakeBase : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeElementBase> SnakeElementBase;


	UPROPERTY(EditDefaultsOnly)
	float ElementSize;

	UPROPERTY()
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
	EMovementDirection LastMoveDirection;

	UPROPERTY(EditDefaultsOnly)
	float MovementSpeed;

	UPROPERTY()
	TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY()
	USnakeElementsShow* CurrentSnakeElementsWidget;

	FTimerHandle UnUsedHandle;

	UPROPERTY(EditAnywhere, Category = "Hunger")
	TSubclassOf<class UUserWidget> HungerWidgetClass;

	float HungerTime;

	UPROPERTY(EditDefaultsOnly)
	float TotalHungerTime;

	UPROPERTY()
	UHungerWidget* HungerWidget;

	FTimerHandle CollisionTimerHandle;

	bool IsInvincibleForObtacles;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddSnakeElement(int ElementsNum = 1);

	void Move();
	UFUNCTION()
	void SnakeElementOverlapped(ASnakeElementBase* OverlappedElement, AActor* Other);

	void RemoveSnakeElement(int NumElementsToRemove);

	void SetWidgetText();

	void Hunger(float time);
	void ToDoAfterTimerOff();
	void UpdateHungerProgress();
	void ShowHungerWidget();
	

	void EnableNoCollision(float time);
	void EnableOverlapAllCollision();


};