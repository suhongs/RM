// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RMHUDWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"

void URMHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	// 초기화용
}

void URMHUDWidget::SetHealth(float Current, float Max)
{
	if (PB_Health)
		PB_Health->SetPercent(Max > 0 ? Current / Max : 0);

	if (TXT_Health)
		TXT_Health->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Current, Max)));
}

void URMHUDWidget::SetMana(float Current, float Max)
{
	if (PB_Mana)
		PB_Mana->SetPercent(Max > 0 ? Current / Max : 0);

	if (TXT_Mana)
		TXT_Mana->SetText(FText::FromString(FString::Printf(TEXT("%.0f / %.0f"), Current, Max)));
}

