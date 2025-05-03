// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/RMGameplayAbilityApproach_Enemy.h"
#include "RMGameplayAbilityApproach_Enemy.h"
#include "Character/RMCharacterBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void URMGameplayAbilityApproach_Enemy::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

AActor* URMGameplayAbilityApproach_Enemy::GetTarget()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	ARMCharacterBase* OwnerCharacter = Cast<ARMCharacterBase>(AvatarActor);
	if (!OwnerCharacter) return nullptr;

	AController* Controller = OwnerCharacter->GetController();
	AAIController* AIController = Cast<AAIController>(Controller);
	if (!AIController) return nullptr;

	UBlackboardComponent* Blackboard = AIController->GetBlackboardComponent();
	if (!Blackboard) return nullptr;

	AActor* Target = Cast<AActor>(Blackboard->GetValueAsObject("TargetActor"));
	return Target;
}
