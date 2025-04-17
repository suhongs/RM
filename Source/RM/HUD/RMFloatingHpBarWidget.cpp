// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RMFloatingHpBarWidget.h"
#include "Components/ProgressBar.h"

void URMFloatingHpBarWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void URMFloatingHpBarWidget::SetHealth(float Current, float Max)
{
	if (PB_Health)
		PB_Health->SetPercent(Max > 0 ? Current / Max : 0);
}
