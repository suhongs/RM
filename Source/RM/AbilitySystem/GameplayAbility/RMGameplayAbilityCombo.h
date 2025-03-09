// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/GameplayAbility/RMGameplayAbilityBase.h"
#include "RMGameplayAbilityCombo.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMGameplayAbilityCombo : public URMGameplayAbilityBase
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION()
	void OnEndAbility();

	UFUNCTION()
	virtual void OnComboWindowOpen(FGameplayEventData Payload);

	UFUNCTION()
	virtual void OnComboWindowEnd(FGameplayEventData Payload);

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CurrentComboWindowTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag PrevComboWindowTag;
	
	
};
