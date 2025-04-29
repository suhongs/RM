// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/RMBTTaskBase.h"
#include "AIController.h"
#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

URMBTTaskBase::URMBTTaskBase()
{
}

EBTNodeResult::Type URMBTTaskBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
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

    FGameplayTag LightAttackTag = FGameplayTag::RequestGameplayTag(FName("Player.Attack.LightAttack"));

    FGameplayTagContainer TagContainer;
    TagContainer.AddTag(LightAttackTag);

    bool result = ASC->TryActivateAbilitiesByTag(TagContainer);

    return result ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
}
