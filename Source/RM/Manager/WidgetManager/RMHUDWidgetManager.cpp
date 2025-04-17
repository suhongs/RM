// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WidgetManager/RMHUDWidgetManager.h"
#include "HUD/RMHUDWidget.h"
#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAttributeSet.h"

void URMHUDWidgetManager::InitWidget()
{
	Super::InitWidget();

	//AttributeSet°ú Bind
	BindCallbacksToDependencies();
	BroadcastInitialValues();

}

void URMHUDWidgetManager::BroadcastInitialValues()
{
	if (Pawn == nullptr)
	{
		return;
	}

	URMAttributeSet* AttributeSet = Pawn->GetAttributeSet();
	if (AttributeSet == nullptr)
	{
		return;
	}

	if (Widget == nullptr)
	{
		return;
	}

	if (URMHUDWidget* HUDWidget = Cast<URMHUDWidget>(Widget))
	{
		HUDWidget->SetHealth(AttributeSet->GetCurrentHealth(), AttributeSet->GetMaxHealth());
		HUDWidget->SetMana(AttributeSet->GetCurrentMana(), AttributeSet->GetMaxMana());
	}
}

void URMHUDWidgetManager::BindCallbacksToDependencies()
{
	if (Pawn == nullptr)
	{
		return;
	}

	URMAttributeSet* AttributeSet = Pawn->GetAttributeSet();
	if (AttributeSet == nullptr)
	{
		return;
	}

	if (Widget == nullptr)
	{
		return;
	}

	if (URMHUDWidget* HUDWidget = Cast<URMHUDWidget>(Widget))
	{
		AttributeSet->OnHealthChanged.AddUObject(HUDWidget, &URMHUDWidget::SetHealth);
		AttributeSet->OnManaChanged.AddUObject(HUDWidget, &URMHUDWidget::SetMana);
	}	
	
}
