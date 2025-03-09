// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "RMPlayerState.generated.h"

class UAttributeSet;

UCLASS()
class RM_API ARMPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ARMPlayerState();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
	UAttributeSet* GetAttributeSet() const;
	
};
