// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMEnemyCharacter.h"
#include "HUD/RMFloatingHpBarWidgetComponent.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"

ARMEnemyCharacter::ARMEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<URMAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<URMAttributeSet>("AttributeSet");

	FloatingHpBarWidgetComponent = CreateDefaultSubobject<URMFloatingHpBarWidgetComponent>(TEXT("FloatingHpBarWidget"));
	FloatingHpBarWidgetComponent->SetupAttachment(RootComponent); // 루트에 부착
	FloatingHpBarWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f)); // 캐릭터 머리 위로 이동 (필요시 조절)
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

	if (FloatingHpBarWidgetComponent && AttributeSet)
	{
		FloatingHpBarWidgetComponent->InitFloatingWidgetComponent(AttributeSet);
	}
}

void ARMEnemyCharacter::InitAbilityActorInfo()
{
	if (AbilitySystemComponent == nullptr)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}
