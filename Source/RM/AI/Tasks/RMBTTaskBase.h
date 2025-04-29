// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "RMBTTaskBase.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class RM_API URMBTTaskBase : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	URMBTTaskBase();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
