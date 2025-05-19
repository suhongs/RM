// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GameplayAbility/RMGameplayAbilityApproach.h"
#include "Character/RMCharacterBase.h"
#include "CombatSystem/RMLockOnSystemComponent.h"

void URMGameplayAbilityApproach::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	ARMCharacterBase* OwnerCharacter = Cast<ARMCharacterBase>(AvatarActor);
	if (!OwnerCharacter) return;

	AActor* Target = GetTarget();
	if (!IsValid(Target))
		return;

	/*
		StartLocation	: 현재 내 캐릭터의 위치
		Direction		: 내 캐릭터에서 Target까지의 방향 vector
		Distance		: 내 캐릭터와 Target과의 거리
		EndLocation		: 돌진 후 최종 위치
	*/
	const FVector StartLocation = OwnerCharacter->GetActorLocation();
	const FVector Direction = (Target->GetActorLocation() - StartLocation).GetSafeNormal();
	const float Distance = FMath::Min(FVector::Dist(Target->GetActorLocation(), StartLocation) * 0.8f, MaxApproachDistance);
	const FVector EndLocation = StartLocation + Direction * Distance;

	ElapsedTime = 0.0f;
	Duration = (MoveSpeed > 0.f) ? Distance / MoveSpeed : 0.3f; // 속도로 Duration 계산

	// 타이머 시작
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_ApproachMove,
		[this, OwnerCharacter, Target, StartLocation, EndLocation]() mutable
		{
			if (!OwnerCharacter || !Target)
			{
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ApproachMove);
				EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
				return;
			}

			/*
				돌진기는 순간이동이 아니기 때문에 EndLocation에 바로 위치 시키는 것이 아닌
				Alpha 보간을 활용해 EndLocation까지 점진적으로 이동시킴
			*/

			ElapsedTime += TickInterval;
			const float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.f, 1.f);
			const FVector NewLocation = FMath::Lerp(StartLocation, EndLocation, Alpha);

			OwnerCharacter->SetActorLocation(NewLocation, true);

			if (Alpha >= 1.f)
			{
				GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ApproachMove);
			}
		},
		TickInterval,
		true
	);
}

AActor* URMGameplayAbilityApproach::GetTarget()
{
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	ARMCharacterBase* OwnerCharacter = Cast<ARMCharacterBase>(AvatarActor);
	if (!OwnerCharacter) return nullptr;

	URMLockOnSystemComponent* LockOnComp = OwnerCharacter->FindComponentByClass<URMLockOnSystemComponent>();
	if (!LockOnComp || !LockOnComp->LockedTarget) return nullptr;

	return LockOnComp->LockedTarget;
}
