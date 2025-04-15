// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RMGameplayAbilityBase.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMGameplayAbilityBase : public UGameplayAbility
{
	GENERATED_BODY()
	
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MontageAbility)
	TObjectPtr<UAnimMontage> 	MontageToPlay;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	float	PlayRate;

	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	FName	SectionName;

	/** GameplayEffects to apply and then remove while the animation is playing */
	UPROPERTY(EditDefaultsOnly, Category = MontageAbility)
	TArray<TSubclassOf<UGameplayEffect>> GameplayEffectClassesWhileAnimating;

	/** Deprecated. Use GameplayEffectClassesWhileAnimating instead. */
	UPROPERTY(VisibleDefaultsOnly, Category = Deprecated)
	TArray<TObjectPtr<const UGameplayEffect>>	GameplayEffectsWhileAnimating;

	UFUNCTION()
	virtual void OnEndAbility();

	void GetGameplayEffectsWhileAnimating(TArray<const UGameplayEffect*>& OutEffects) const;
	
	
};
