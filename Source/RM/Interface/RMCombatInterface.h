// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RMCombatInterface.generated.h"

struct FRMSkillId;
// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class URMCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RM_API IRMCombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void HitDetection(const FRMSkillId& InSkillId) = 0;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void HitReact() = 0;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	virtual void ClearHitActors() = 0;
};
