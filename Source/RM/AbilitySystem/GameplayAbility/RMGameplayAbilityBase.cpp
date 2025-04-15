// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/RMGameplayAbilityBase.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"

void URMGameplayAbilityBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

	if (MontageToPlay != nullptr && AnimInstance != nullptr)
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

		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,   // Owning Ability
			NAME_None, // Task Name (태그로 구분 가능)
			MontageToPlay, // 재생할 애니메이션 몽타주
			PlayRate,   // 플레이 속도
			SectionName, // StartSectionName (특정 섹션에서 시작하려면 지정)
			true,   // bStopWhenAbilityEnds (능력 종료 시 애니메이션 멈춤 여부)
			1.0f     // AnimRootMotionTranslationScale (루트 모션 배율)
		);

		if (MontageTask)
		{
			MontageTask->OnCompleted.AddDynamic(this, &URMGameplayAbilityBase::OnEndAbility);
			MontageTask->OnInterrupted.AddDynamic(this, &URMGameplayAbilityBase::OnEndAbility);
			MontageTask->OnCancelled.AddDynamic(this, &URMGameplayAbilityBase::OnEndAbility);

			MontageTask->ReadyForActivation();
		}
	}
	else
	{
		OnEndAbility();
	}
}



void URMGameplayAbilityBase::OnEndAbility()
{
	bool bReplicateEndAbility = false;
	bool bWasCancelled = true;

	Super::EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void URMGameplayAbilityBase::GetGameplayEffectsWhileAnimating(TArray<const UGameplayEffect*>& OutEffects) const
{
}
