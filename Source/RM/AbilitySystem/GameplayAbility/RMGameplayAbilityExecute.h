// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/RMGameplayAbilityCombo.h"
#include "RMGameplayAbilityExecute.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMGameplayAbilityExecute : public URMGameplayAbilityCombo
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
	virtual AActor* GetTarget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitReact")
	FGameplayTag HitReactTag; // 기본값 예시
	
};
