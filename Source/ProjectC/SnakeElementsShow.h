// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "SnakeElementsShow.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTC_API USnakeElementsShow : public UUserWidget
{
	GENERATED_BODY()
	
    public:
        UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        UTextBlock* TextBlock;
        
        UFUNCTION(BlueprintCallable)
        void SetSnakeElementCount(int32 Count);
};
