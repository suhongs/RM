// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "RMCostCalulation.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMCostCalulation : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
	
	
public:
	float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
};
