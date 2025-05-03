// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/RMBTTask_ActiveAbility.h"
#include "AIController.h"
#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"

URMBTTask_ActiveAbility::URMBTTask_ActiveAbility()
{
}

EBTNodeResult::Type URMBTTask_ActiveAbility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

    if (!AbilityTag.IsValid())
    {
        return EBTNodeResult::Failed;
    }

    AAIController* AIController = OwnerComp.GetAIOwner();
    APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;

    if (!Pawn)
    {
        return EBTNodeResult::Failed;
    }

    ARMCharacterBase* Character = Cast<ARMCharacterBase>(Pawn);
    if (!IsValid(Character))
    {
        return EBTNodeResult::Failed;
    }

    UAbilitySystemComponent* ASC = Character->GetAbilitySystemComponent();
    if (!IsValid(ASC))
    {
        return EBTNodeResult::Failed;
    }

    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(AbilityTag);


    bool result = ASC->TryActivateAbilitiesByTag(TagContainer);

    return result ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
