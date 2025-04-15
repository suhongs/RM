// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/HitProcessingSubsystem.h"
#include "Subsystem/RMDataManagerSubsystem.h"
#include "Character/RMCharacterBase.h"
#include "DataTable/RMSkillData.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"

void UHitProcessingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UHitProcessingSubsystem::ProcessHit(ARMCharacterBase* InstigatorActor, ARMCharacterBase* TargetActor, const FRMSkillId& SkillId)
{
	const FRMSkillData* SkillData = GetSkillDataById(SkillId);
	if (!SkillData || !TargetActor) return;

	// ¿¹: GameplayEffect Àû¿ë
	if (SkillData->Effects)
	{
		if (UAbilitySystemComponent* TargetASC = TargetActor->GetAbilitySystemComponent())
		{
			FGameplayEffectContextHandle Context = TargetASC->MakeEffectContext();
			Context.AddSourceObject(InstigatorActor);

			FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(SkillData->Effects, 1.0f, Context);
			if (SpecHandle.IsValid())
			{
				TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			}
		}
	}
}

const FRMSkillData* UHitProcessingSubsystem::GetSkillDataById(const FRMSkillId& InSkillId)
{
	if (const UGameInstance* GI = GetGameInstance())
	{
		if (URMDataManagerSubsystem* DataManager = GI->GetSubsystem<URMDataManagerSubsystem>())
		{
			return DataManager->FindRow<FRMSkillData>(FName("Skill"), InSkillId.ToRowName());
			
		}
	}

	return nullptr;
}


