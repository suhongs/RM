// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/RMGameplayAbilityCombo.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "Animation/AnimInstance.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEvent.h"


void URMGameplayAbilityCombo::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		return;
	}

	UAnimInstance* AnimInstance = ActorInfo->GetAnimInstance();

	if (MontageToPlay != nullptr && AnimInstance != nullptr)
	{
		UAbilitySystemComponent* AbilitySystemComponent = ActorInfo->AbilitySystemComponent.Get();
		if (AbilitySystemComponent)
		{

			UAbilityTask_WaitGameplayEvent* ComboWindowOpenEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
				this,
				FGameplayTag::RequestGameplayTag(FName("Event.ComboWindowOpen")),
				nullptr,
				false,
				true
			);

			if (ComboWindowOpenEvent)
			{
				ComboWindowOpenEvent->EventReceived.AddDynamic(this, &URMGameplayAbilityCombo::OnComboWindowOpen);

				ComboWindowOpenEvent->ReadyForActivation();
			}

			UAbilityTask_WaitGameplayEvent* ComboWindowEndEvent = UAbilityTask_WaitGameplayEvent::WaitGameplayEvent(
				this,
				FGameplayTag::RequestGameplayTag(FName("Event.ComboWindowClose")),
				nullptr,
				false,
				true
			);

			if (ComboWindowEndEvent)
			{
				ComboWindowEndEvent->EventReceived.AddDynamic(this, &URMGameplayAbilityCombo::OnComboWindowEnd);

				ComboWindowEndEvent->ReadyForActivation();
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
				MontageTask->OnCompleted.AddDynamic(this, &URMGameplayAbilityCombo::OnEndAbility);
				MontageTask->OnInterrupted.AddDynamic(this, &URMGameplayAbilityCombo::OnEndAbility);
				MontageTask->OnCancelled.AddDynamic(this, &URMGameplayAbilityCombo::OnEndAbility);
				MontageTask->OnBlendOut.AddDynamic(this, &URMGameplayAbilityCombo::OnEndAbility);

				MontageTask->ReadyForActivation();
			}

		}
	}
}

void URMGameplayAbilityCombo::OnEndAbility()
{
	RemoveAllComboWindowTag();

	bool bReplicateEndAbility = false;
	bool bWasCancelled = true;

	if (PrevComboWindowTag.IsValid())
	{
		if (auto ASC = GetAbilitySystemComponentFromActorInfo())
		{
			ASC->RemoveLooseGameplayTag(PrevComboWindowTag);
		}
	}

	Super::EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void URMGameplayAbilityCombo::OnComboWindowOpen(FGameplayEventData Payload)
{
	FGameplayAbilityActorInfo ActorInfo = GetActorInfo();
	if (!ActorInfo.AbilitySystemComponent.IsValid())
	{
		return;
	}


	UAbilitySystemComponent* AbilitySystemComponent = ActorInfo.AbilitySystemComponent.Get();
	if (AbilitySystemComponent)
	{
		if (PrevComboWindowTag.IsValid())
		{
			AbilitySystemComponent->RemoveLooseGameplayTag(PrevComboWindowTag);
		}

		if (CurrentComboWindowTag.IsValid())
		{
			AbilitySystemComponent->AddLooseGameplayTag(CurrentComboWindowTag);
		}
	}
}

void URMGameplayAbilityCombo::OnComboWindowEnd(FGameplayEventData Payload)
{
	RemoveAllComboWindowTag();
	OnEndAbility();
}

void URMGameplayAbilityCombo::RemoveAllComboWindowTag()
{
	FGameplayAbilityActorInfo ActorInfo = GetActorInfo();
	if (!ActorInfo.AbilitySystemComponent.IsValid())
	{
		return;
	}


	UAbilitySystemComponent* AbilitySystemComponent = ActorInfo.AbilitySystemComponent.Get();
	if (AbilitySystemComponent)
	{
		if (CurrentComboWindowTag.IsValid())
		{
			AbilitySystemComponent->RemoveLooseGameplayTag(CurrentComboWindowTag);
		}
	}
}
