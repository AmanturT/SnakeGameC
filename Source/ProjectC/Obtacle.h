// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Obtacle.generated.h"
class AGeneration;
UCLASS()
class PROJECTC_API AObtacle : public AActor, public IInteractable
{
	GENERATED_BODY()


	UPROPERTY(EditDefaultsOnly)
	float LifeTimeOfObtacle;

	UPROPERTY(EditDefaultsOnly)
	bool IsObtacleImmortal;

	UPROPERTY(EditDefaultsOnly)
	bool IsObtacleBarrier;

	UPROPERTY(EditDefaultsOnly)
	bool IsObtacleGameField;

	AGeneration* GenerationClass;


	float CurrentLifeTime;
	FTimerHandle LifeTimeTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UTextRenderComponent* LifeTimeTextComponent;
	
public:	
	// Sets default values for this actor's properties
	AObtacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactor, bool bIsHead) override;

	
	UFUNCTION()
	void DestroyObtacle();
	void UpdateLifeTimeText();
	void LifeTimeTick();
};
