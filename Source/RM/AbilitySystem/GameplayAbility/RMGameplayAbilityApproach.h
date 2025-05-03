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
	/** �̵� �ӵ� (cm/s) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Approach")
	float MoveSpeed = 1500.f;

	/** Ÿ�̸� ƽ ���� (��) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Approach")
	float TickInterval = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Approach")
	float MaxApproachDistance = 800.f; // �⺻�� ����

protected:
	FTimerHandle TimerHandle_ApproachMove;

	/** ���� �̵� ��� �ð� */
	float ElapsedTime = 0.0f;

	/** ���ο��� ���� �̵� ���� �ð� */
	float Duration = 0.0f;
};
