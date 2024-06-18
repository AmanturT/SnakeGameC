// Fill out your copyright notice in the Description page of Project Settings.
#include "HungerWidget.h"
#include "Components/ProgressBar.h"



void UHungerWidget::NativeConstruct()
{
	Super::NativeConstruct();
}
void UHungerWidget::SetHungerProgress(float Progress)
{
	if (HungerProgressBar)
	{
		HungerProgressBar->SetPercent(Progress);
	}
}


