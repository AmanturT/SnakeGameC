// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HungerWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UHungerWidget : public UUserWidget
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintCallable, Category = "Hunger")
		void SetHungerProgress(float Progress);

	protected:
		virtual void NativeConstruct() override;
		UPROPERTY(meta = (BindWidget))
		class UProgressBar* HungerProgressBar;
	
};
