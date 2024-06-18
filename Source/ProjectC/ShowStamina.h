// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShowStamina.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API UShowStamina : public UUserWidget
{
	GENERATED_BODY()
	public:
		UFUNCTION(BlueprintCallable, Category = "Hunger")
		void SetStaminaProgressBar(float Progress);

	protected:
		virtual void NativeConstruct() override;
		UPROPERTY(meta = (BindWidget))
		class UProgressBar* StaminaProgressBar;

};
