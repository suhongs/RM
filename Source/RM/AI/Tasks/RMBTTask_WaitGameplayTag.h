// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Tasks/RMBTTaskBase.h"
#include "RMBTTask_WaitGameplayTag.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMBTTask_WaitGameplayTag : public URMBTTaskBase
{
	GENERATED_BODY()
	
public:
	URMBTTask_WaitGameplayTag();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UPROPERTY(EditAnywhere)
	float Interval = 0.05f;

	UPROPERTY(EditAnywhere)
	float TotalTime = 2.f;

	UPROPERTY(EditAnywhere)
	float ElapsedTime = 0.f;
	
private:
	UPROPERTY(EditAnywhere, Category = "Tags")
	FGameplayTagContainer RequiredTags;
	
};
