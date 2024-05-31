// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementsShow.h"
#include "Components/TextBlock.h"

void USnakeElementsShow::NativeConstruct()
{
    Super::NativeConstruct();
    if (!ElementCountText)
    {
        UE_LOG(LogTemp, Error, TEXT("ElementCountText is not bound to the widget!1"));
    }
}

void USnakeElementsShow::UpdateElementCount(int32 ElementCount)
{
    if (ElementCountText)
    {
        ElementCountText->SetText(FText::FromString(FString::Printf(TEXT("Elements: %d"), ElementCount)));
       
    }
    
    else
    {
        UE_LOG(LogTemp, Error, TEXT("ElementCountText is not bound to the widget!2"));
    }
}
