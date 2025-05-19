// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/RMQuest.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "Character/RMCharacterBase.h"


void URMQuest::Initialize(FName InQuestID, ARMCharacterBase* InOwner)
{
    QuestID = InQuestID;
    QuestOwner = InOwner;
}

const bool URMQuest::CouldComplete() const
{
    return CurrentCount >= TargetCount;
}

void URMQuest::Complete()
{
    bIsCompleted = true;

    if (!IsValid(QuestOwner))
        return;

    UAbilitySystemComponent* ASC = QuestOwner->GetAbilitySystemComponent();
    if (!IsValid(ASC))
        return;

    for (auto SkillReward : SkillRewards)
    {
        if (!IsValid(SkillReward))
            continue;

        ASC->GiveAbility(FGameplayAbilitySpec(SkillReward, 0, 0));
    }
}

void URMQuest::IncreaseKillCount()
{
    CurrentCount = FMath::Min(CurrentCount + 1, TargetCount);
}
