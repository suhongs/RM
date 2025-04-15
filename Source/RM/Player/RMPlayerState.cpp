// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RMPlayerState.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"

ARMPlayerState::ARMPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<URMAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<URMAttributeSet>("AttributeSet");
}
