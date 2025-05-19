// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMEnemyCharacter.h"
#include "HUD/RMFloatingHpBarWidgetComponent.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"
#include "HUD/RMInbodyCursorWidgetComponent.h"
#include "Subsystem/RMFloatingDamageSubsystem.h"
#include "Subsystem/RMQuestSubsystem.h"

ARMEnemyCharacter::ARMEnemyCharacter()
{
	AbilitySystemComponent = CreateDefaultSubobject<URMAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<URMAttributeSet>("AttributeSet");

	FloatingHealthBarWidgetComponent = CreateDefaultSubobject<URMFloatingHpBarWidgetComponent>(TEXT("FloatingHpBarWidgetComponent"));
	FloatingHealthBarWidgetComponent->SetupAttachment(RootComponent); // 루트에 부착
	FloatingHealthBarWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 120.f)); // 캐릭터 머리 위로 이동 (필요시 조절)

	InbodyCursorWidgetComponent = CreateDefaultSubobject<URMInbodyCursorWidgetComponent>(TEXT("InbodyCursorWidgetComponent"));
	InbodyCursorWidgetComponent->SetupAttachment(RootComponent);
}

void ARMEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	InitDefaultAbility();
	Super::InitDefaultAttributes();

	if (IsValid(AttributeSet))
	{
		AttributeSet->OnCharacterDead.AddDynamic(this, &ARMEnemyCharacter::CharacterDead);
	}

}

void ARMEnemyCharacter::HitDetection(const FRMSkillId& InSkillId)
{
	Super::HitDetection(InSkillId);
}

void ARMEnemyCharacter::HitReact()
{
	Super::HitReact();

}

void ARMEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (FloatingHealthBarWidgetComponent && AttributeSet && AbilitySystemComponent)
	{
		FloatingHealthBarWidgetComponent->InitFloatingWidgetComponent(AbilitySystemComponent, AttributeSet);
	}

	URMFloatingDamageSubsystem* FloatingDamageSubsystem = GetGameInstance()->GetSubsystem<URMFloatingDamageSubsystem>();
	if (IsValid(FloatingDamageSubsystem))
	{
		FloatingDamageSubsystem->RegisterWithAbilitySystem(this);
	}


}

void ARMEnemyCharacter::InitAbilityActorInfo()
{
	if (AbilitySystemComponent == nullptr)
		return;

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ARMEnemyCharacter::CharacterDead()
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
		return;

	URMQuestSubsystem* QuestSubsystem = World->GetGameInstance()->GetSubsystem<URMQuestSubsystem>();
	if (!IsValid(QuestSubsystem))
		return;

	QuestSubsystem->OnMonsterKilled(CharacterName);

	Destroy();
}

void ARMEnemyCharacter::ShowInbodyCursor()
{
	if (IsValid(InbodyCursorWidgetComponent))
	{
		InbodyCursorWidgetComponent->SetVisibility(true);
	}
}

void ARMEnemyCharacter::HideInbodyCursor()
{
	if (IsValid(InbodyCursorWidgetComponent))
	{
		InbodyCursorWidgetComponent->SetVisibility(false);
	}
}
