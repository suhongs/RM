// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WidgetManager/RMHUDWidgetManager.h"
#include "HUD/RMHUDWidget.h"
#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAttributeSet.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"

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

	if (!IsValid(AbilitySystemComponent))
	{
		return;
	}

	if (URMHUDWidget* HUDWidget = Cast<URMHUDWidget>(Widget))
	{

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &URMHUDWidgetManager::SetHealthProgressBar);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentManaAttribute()).AddUObject(this, &URMHUDWidgetManager::SetManaProgressBar);


		//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetCurrentHealthAttribute()).AddLambda()
		//AttributeSet->OnHealthChanged.AddUObject(HUDWidget, &URMHUDWidget::SetHealth);
		//AttributeSet->OnManaChanged.AddUObject(HUDWidget, &URMHUDWidget::SetMana);
	}	
	
}

void URMHUDWidgetManager::SetHealthProgressBar(const FOnAttributeChangeData& Data)
{
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
		HUDWidget->SetHealth(Data.NewValue, AttributeSet->GetMaxHealth());
	}
}

void URMHUDWidgetManager::SetManaProgressBar(const FOnAttributeChangeData& Data)
{
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
		HUDWidget->SetMana(Data.NewValue, AttributeSet->GetMaxMana());
	}
}

