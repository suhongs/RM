// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"
#include "AbilitySystem/GameplayEffect/RMGameplayEffectBase.h"


// Sets default values
ARMCharacterBase::ARMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARMCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ARMCharacterBase::InitAbilityActorInfo()
{

}

void ARMCharacterBase::InitDefaultAbility()
{
	if (IsValid(AbilitySystemComponent) == false)
		return;

	for (auto Ability : DefaultAbilities)
	{
		if (IsValid(Ability) == false)
			continue;

		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 0, 0, this));
	}
}

// Called every frame
void ARMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARMCharacterBase::InitDefaultAttributes()
{
	if (AbilitySystemComponent && DefaultStatEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultStatEffect, 1.0f, EffectContext);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ARMCharacterBase::HitDetection(const FRMSkillId& InSkillId)
{

}

void ARMCharacterBase::HitReact()
{
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	FGameplayTag HitReactTag = FGameplayTag::RequestGameplayTag(FName("Common.Combat.HitReact"));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(HitReactTag);

	bool result = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void ARMCharacterBase::ClearHitActors()
{
	HitActors.Empty();
}

UAbilitySystemComponent* ARMCharacterBase::GetAbilitySystemComponent() const
{
	return this->AbilitySystemComponent;
}

