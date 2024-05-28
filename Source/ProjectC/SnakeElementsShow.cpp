// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeElementsShow.h"
#include "Components/TextBlock.h"





void USnakeElementsShow::SetSnakeElementCount(int32 Count)
{
   
        FString Text = FString::FromInt(Count);
        Text.Append(" Elements");
        TextBlock->SetText(FText::FromString(Text));
    
   
}
