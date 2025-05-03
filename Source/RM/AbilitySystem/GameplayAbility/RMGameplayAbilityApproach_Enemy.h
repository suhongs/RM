// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/RMGameplayAbilityApproach.h"
#include "RMGameplayAbilityApproach_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMGameplayAbilityApproach_Enemy : public URMGameplayAbilityApproach
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

private:
	virtual AActor* GetTarget() override;
	
};
