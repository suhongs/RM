// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/RMGameplayAbilityBase.h"
#include "RMGameplayAbilityApproach.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMGameplayAbilityApproach : public URMGameplayAbilityBase
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

protected:
	/** 이동 속도 (cm/s) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Approach")
	float MoveSpeed = 1500.f;

	/** 타이머 틱 간격 (초) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Approach")
	float TickInterval = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Approach")
	float MaxApproachDistance = 800.f; // 기본값 예시

protected:
	FTimerHandle TimerHandle_ApproachMove;

	/** 현재 이동 경과 시간 */
	float ElapsedTime = 0.0f;

	/** 내부에서 계산된 이동 지속 시간 */
	float Duration = 0.0f;
};
