// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowStamina.h"
#include "Components/ProgressBar.h"

void UShowStamina::NativeConstruct()
{
	Super::NativeConstruct();
}

void UShowStamina::SetStaminaProgressBar(float Progress)
{
	StaminaProgressBar->SetPercent(Progress);
}


