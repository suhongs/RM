// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMEnemyCharacter.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"

ARMEnemyCharacter::ARMEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<URMAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<URMAttributeSet>("AttributeSet");
}

void ARMEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	InitDefaultAbility();
	Super::InitDefaultAttributes();
}

void ARMEnemyCharacter::HitDetection(const FRMSkillId& InSkillId)
{
}

void ARMEnemyCharacter::HitReact()
{
	Super::HitReact();

}

void ARMEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ARMEnemyCharacter::InitAbilityActorInfo()
{
	if (AbilitySystemComponent == nullptr)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
