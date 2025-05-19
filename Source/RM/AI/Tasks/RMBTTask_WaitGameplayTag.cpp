// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/RMBTTask_WaitGameplayTag.h"
#include "AIController.h"
#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"

URMBTTask_WaitGameplayTag::URMBTTask_WaitGameplayTag()
{

}

EBTNodeResult::Type URMBTTask_WaitGameplayTag::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ElapsedTime = 0;
	bNotifyTick = true;
	return EBTNodeResult::InProgress;
}

void URMBTTask_WaitGameplayTag::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ElapsedTime += DeltaSeconds;

	AAIController* AIController = OwnerComp.GetAIOwner();
	APawn* Pawn = AIController ? AIController->GetPawn() : nullptr;
	ARMCharacterBase* Character = Pawn ? Cast<ARMCharacterBase>(Pawn) : nullptr;
	UAbilitySystemComponent* AbilitySystemComponent = Character ? Character->GetAbilitySystemComponent() : nullptr;

	if (!IsValid(AbilitySystemComponent))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	if (AbilitySystemComponent->HasAnyMatchingGameplayTags(RequiredTags))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (ElapsedTime >= TotalTime)  // 시간 초과 시 실패 처리
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
}
