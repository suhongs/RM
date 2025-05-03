// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AI/Tasks/RMBTTaskBase.h"
#include "RMBTTask_ActiveAbility.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMBTTask_ActiveAbility : public URMBTTaskBase
{
	GENERATED_BODY()
	
public:
	URMBTTask_ActiveAbility();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
public:
	UPROPERTY(EditAnywhere, Category = "Ability")
	FGameplayTag AbilityTag;
};
