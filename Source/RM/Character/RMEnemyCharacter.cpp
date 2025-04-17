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
	FloatingHpBarWidgetComponent->SetupAttachment(RootComponent); // ��Ʈ�� ����
	FloatingHpBarWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f)); // ĳ���� �Ӹ� ���� �̵� (�ʿ�� ����)
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
