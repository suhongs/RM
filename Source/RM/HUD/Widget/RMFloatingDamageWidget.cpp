// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Widget/RMFloatingDamageWidget.h"
#include "RMFloatingDamageWidget.h"
#include "Components/TextBlock.h"

void URMFloatingDamageWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void URMFloatingDamageWidget::SetDamageText(float InDamage)
{
	if (TXT_FloatingDamage)
		TXT_FloatingDamage->SetText(FText::FromString(FString::Printf(TEXT("%.0f"),InDamage)));

}


