// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/RMAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameplayEffect.h"

URMAttributeSet::URMAttributeSet()
{
}

void URMAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		AdjustChangeMaxAttribute(CurrentHealth, MaxHealth, NewValue, GetCurrentHealthAttribute());
	}
	else if (Attribute == GetMaxManaAttribute())
	{
		AdjustChangeMaxAttribute(CurrentMana, MaxMana, NewValue, GetCurrentManaAttribute());
	}
}

void URMAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	
	if (Attribute == GetCurrentHealthAttribute())
	{
		OnHealthChanged.Broadcast(NewValue, GetMaxHealth());
		if (NewValue <= 0.f)
		{
			if (OnCharacterDead.IsBound())
			{
				OnCharacterDead.Broadcast();
			}
		}
	}

	if (Attribute == GetCurrentManaAttribute())
	{
		OnManaChanged.Broadcast(NewValue, GetMaxMana());
	}
}

void URMAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentManaAttribute())
	{
		SetCurrentMana(FMath::Clamp(GetCurrentMana(), 0.f, GetMaxMana()));
	}
	
}

void URMAttributeSet::AdjustChangeMaxAttribute(FGameplayAttributeData& CurrentAttribute, const FGameplayAttributeData& MaxAttribute, float NewValue, const FGameplayAttribute& AffectAttributeProperty)
{
	UAbilitySystemComponent* AbilitySystemComponent = GetOwningAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent))
		return;

	const float CurrentMax = MaxAttribute.GetCurrentValue();

	if (FMath::IsNearlyEqual(CurrentMax, NewValue) == false)
	{
		const float current = CurrentAttribute.GetCurrentValue();
		float delta = (0 <= CurrentMax) ? (NewValue - CurrentMax) : NewValue;

		AbilitySystemComponent->ApplyModToAttributeUnsafe(AffectAttributeProperty, EGameplayModOp::Additive, delta);
	}
}
