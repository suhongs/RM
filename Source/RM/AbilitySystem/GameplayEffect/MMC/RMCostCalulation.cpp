// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayEffect/MMC/RMCostCalulation.h"
#include "AbilitySystem/GameplayAbility/RMGameplayAbilityBase.h"

float URMCostCalulation::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const URMGameplayAbilityBase* Ability = Cast<URMGameplayAbilityBase>(Spec.GetContext().GetAbility());

	if (!IsValid(Ability))
		return 0.f;

	return Ability->Cost;
}

