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
		StartLocation	: ���� �� ĳ������ ��ġ
		Direction		: �� ĳ���Ϳ��� Target������ ���� vector
		Distance		: �� ĳ���Ϳ� Target���� �Ÿ�
		EndLocation		: ���� �� ���� ��ġ
	*/
	const FVector StartLocation = OwnerCharacter->GetActorLocation();
	const FVector Direction = (Target->GetActorLocation() - StartLocation).GetSafeNormal();
	const float Distance = FMath::Min(FVector::Dist(Target->GetActorLocation(), StartLocation) * 0.8f, MaxApproachDistance);
	const FVector EndLocation = StartLocation + Direction * Distance;

	ElapsedTime = 0.0f;
	Duration = (MoveSpeed > 0.f) ? Distance / MoveSpeed : 0.3f; // �ӵ��� Duration ���

	// Ÿ�̸� ����
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
				������� �����̵��� �ƴϱ� ������ EndLocation�� �ٷ� ��ġ ��Ű�� ���� �ƴ�
				Alpha ������ Ȱ���� EndLocation���� ���������� �̵���Ŵ
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
