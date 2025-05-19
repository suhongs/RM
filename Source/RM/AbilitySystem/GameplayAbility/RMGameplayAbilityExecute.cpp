// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/RMGameplayAbilityExecute.h"
#include "Character/RMCharacterBase.h"
#include "CombatSystem/RMLockOnSystemComponent.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"


void URMGameplayAbilityExecute::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	ARMCharacterBase* OwnerCharacter = Cast<ARMCharacterBase>(AvatarActor);
	if (!OwnerCharacter)
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}

	AActor* Target = GetTarget();
	ARMCharacterBase* TargetCharacter = IsValid(Target) ? Cast<ARMCharacterBase>(Target) : nullptr;
	UAbilitySystemComponent* TargetAbilitySystemComponent = IsValid(TargetCharacter) ? TargetCharacter->GetAbilitySystemComponent() : nullptr;

	if (!IsValid(TargetAbilitySystemComponent))
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		return;
	}


	const FVector StartLocation = OwnerCharacter->GetActorLocation();
	const FVector Direction = (Target->GetActorLocation() - StartLocation).GetSafeNormal();
	const float Distance = FVector::DistSquared(Target->GetActorLocation(), StartLocation);

	if (Distance < FMath::Square(100.f))
	{
		if (TargetAbilitySystemComponent->TryActivateAbilitiesByTag(FGameplayTagContainer(HitReactTag)))
		{
			Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
			UE_LOG(LogTemp, Warning, TEXT("Execute Ability Activated on Both Player and Target"));
		}
		else
		{
			CancelAbility(Handle, ActorInfo, ActivationInfo, true);
		}
		
	}
	else
	{
		CancelAbility(Handle, ActorInfo, ActivationInfo, true);
	}
}

AActor* URMGameplayAbilityExecute::GetTarget()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	ARMCharacterBase* OwnerCharacter = Cast<ARMCharacterBase>(AvatarActor);
	if (!OwnerCharacter) return nullptr;

	URMLockOnSystemComponent* LockOnComp = OwnerCharacter->FindComponentByClass<URMLockOnSystemComponent>();
	if (!LockOnComp || !LockOnComp->LockedTarget) return nullptr;

	return LockOnComp->LockedTarget;
}
