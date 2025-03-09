// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/RMGameplayAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"

void URMGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

	if (MontageToPlay != nullptr && AnimInstance != nullptr && AnimInstance->GetActiveMontageInstance() == nullptr)
	{
		TArray<FActiveGameplayEffectHandle>	AppliedEffects;

		// Apply GameplayEffects
		TArray<const UGameplayEffect*> Effects;
		GetGameplayEffectsWhileAnimating(Effects);
		if (Effects.Num() > 0)
		{
			UAbilitySystemComponent* const AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
			for (const UGameplayEffect* Effect : Effects)
			{
				FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(Effect, 1.f, MakeEffectContext(Handle, ActorInfo));
				if (EffectHandle.IsValid())
				{
					AppliedEffects.Add(EffectHandle);
				}
			}
		}

		UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
		if (AbilitySystemComponent)
		{
			float MontageDuration = AbilitySystemComponent->PlayMontage(this, ActivationInfo, MontageToPlay, PlayRate, SectionName);


			if (MontageDuration > 0.f)
			{
				// Bind Montage End Delegate
				FOnMontageEnded EndDelegate;
				EndDelegate.BindUObject(this, &URMGameplayAbilityBase::OnMontageEnded, ActorInfo->AbilitySystemComponent, AppliedEffects);
				AnimInstance->Montage_SetEndDelegate(EndDelegate, MontageToPlay);

				if (SectionName != NAME_None)
				{
					AnimInstance->Montage_JumpToSection(SectionName, MontageToPlay);
				}
			}
		}
	}
}

void URMGameplayAbilityBase::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted, TWeakObjectPtr<UAbilitySystemComponent> AbilitySystemComponent, TArray<struct FActiveGameplayEffectHandle> AppliedEffects)
{
}

void URMGameplayAbilityBase::GetGameplayEffectsWhileAnimating(TArray<const UGameplayEffect*>& OutEffects) const
{
}
