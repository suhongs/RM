// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RMAttributeSet.h"
#include "GameplayEffectExtension.h"

URMAttributeSet::URMAttributeSet()
{
}

void URMAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	
	if (Attribute == GetCurrentHealthAttribute())
	{
		OnHealthChanged.Broadcast(NewValue, GetMaxHealth());
	}

	if (Attribute == GetCurrentManaAttribute())
	{
		OnManaChanged.Broadcast(NewValue, GetMaxMana());
	}
}

void URMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		if (OnEffectExecuted.IsBound())
		{
			OnEffectExecuted.Broadcast(Data);
		}
	}
	
}
