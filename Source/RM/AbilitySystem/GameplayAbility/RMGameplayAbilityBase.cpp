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
			NAME_None, // Task Name (�±׷� ���� ����)
			MontageToPlay, // ����� �ִϸ��̼� ��Ÿ��
			PlayRate,   // �÷��� �ӵ�
			SectionName, // StartSectionName (Ư�� ���ǿ��� �����Ϸ��� ����)
			true,   // bStopWhenAbilityEnds (�ɷ� ���� �� �ִϸ��̼� ���� ����)
			1.0f     // AnimRootMotionTranslationScale (��Ʈ ��� ����)
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
