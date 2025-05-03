// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/RMLockOnSystemComponent.h"
#include "Character/RMCharacterBase.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/RMLockOnTargetInterface.h"
#include "HUD/RMCrosshairWidget.h"
// Sets default values for this component's properties
URMLockOnSystemComponent::URMLockOnSystemComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URMLockOnSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void URMLockOnSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (LockedTarget)
	{
		RotateTowardTarget(DeltaTime);
	}
}

void URMLockOnSystemComponent::LockOn()
{
	CurrentTargetIndex = 0;

	// 범위 내의 적을 탐지
	FindTargetsInRange();

	if (!IsValidTarget(CurrentTargetIndex))
		return;

	LockedTarget = DetectedTargetsWithDistance[CurrentTargetIndex].Target;

	if (LockedTarget)
	{
		HandleTargetLock(true);
		AdjustMovementForLockOn();
	}
}

void URMLockOnSystemComponent::Unlock()
{
	HandleTargetLock(false);
	LockedTarget = nullptr;
	CurrentTargetIndex = 0;

	ResetMovementAfterUnlock();
}

void URMLockOnSystemComponent::FindTargetsInRange()
{
	DetectedTargetsWithDistance.Empty();

	ARMCharacterBase* Owner = Cast<ARMCharacterBase>(GetOwner());
	if (!IsValid(Owner) || !TargetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("LockOnTarget Class is nullptr"));
		return;
	}

	/*
		모든 Actors를 가져와 거리를 계산 후
		범위 내에 있는 Actor는 DetectedTargetsWithDistance 배열에 추가.
	*/

	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), TargetClass, Targets);

	for (AActor* Target : Targets)
	{
		if (!Target || Target == Owner)
			continue;

		ARMCharacterBase* TargetCharacter = Cast<ARMCharacterBase>(Target);
		if (!IsValid(TargetCharacter))
			continue;

		if (!IsValidCombatTarget(TargetCharacter))
			continue;

		const float Distance = FVector::Dist(Owner->GetActorLocation(), Target->GetActorLocation());
		if (Distance < LockOnRange)
		{
			FLockOnTargetData TargetData = { TargetCharacter, Distance };
			DetectedTargetsWithDistance.Add(TargetData);
		}
	}

	/*
		모든 감지된 적을 거리가 가까운 순으로 정렬
	*/

	DetectedTargetsWithDistance.Sort([](const FLockOnTargetData& A, const FLockOnTargetData& B)
		{
			return A.Distance < B.Distance;
		});
}

void URMLockOnSystemComponent::LockOnNextTarget()
{
	ChangeTarget(1);
}

void URMLockOnSystemComponent::LockOnPrevTarget()
{
	ChangeTarget(-1);
}

void URMLockOnSystemComponent::RotateTowardTarget(float DeltaTime)
{
	AActor* Owner = GetOwner();
	if (!LockedTarget || !Owner) return;

	const FVector Direction = (LockedTarget->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal();
	FRotator CurrentRotation = Owner->GetActorRotation();
	float TargetYaw = Direction.Rotation().Yaw;

	float NewYaw = FMath::FInterpTo(CurrentRotation.Yaw, TargetYaw, DeltaTime, RotationSpeed);
	FRotator NewRotation(CurrentRotation.Pitch, NewYaw, CurrentRotation.Roll);
	Owner->SetActorRotation(NewRotation);

	AdjustCameraRotation(DeltaTime, Direction, Owner);
}

void URMLockOnSystemComponent::AdjustMovementForLockOn()
{
	AActor* Owner = GetOwner();
	ARMCharacterBase* OwnerCharacter = Cast<ARMCharacterBase>(Owner);
	if (UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = 300.f;
		OwnerCharacter->bUseControllerRotationYaw = true;
		MovementComponent->bOrientRotationToMovement = false;
	}
}

void URMLockOnSystemComponent::ResetMovementAfterUnlock()
{
	AActor* Owner = GetOwner();
	ARMCharacterBase* OwnerCharacter = Cast<ARMCharacterBase>(Owner);
	if (UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = 600.f;
		OwnerCharacter->bUseControllerRotationYaw = false;
		MovementComponent->bOrientRotationToMovement = true;
	}
}

bool URMLockOnSystemComponent::IsValidTarget(int32 Index) const
{
	return DetectedTargetsWithDistance.IsValidIndex(Index);
}

bool URMLockOnSystemComponent::IsValidCombatTarget(ARMCharacterBase* Target) const
{
	return Cast<IRMCombatInterface>(Target) && Cast<IRMLockOnTargetInterface>(Target);
}

void URMLockOnSystemComponent::HandleTargetLock(bool bLocking)
{
	if (IRMLockOnTargetInterface* LockOnTargetInterface = Cast<IRMLockOnTargetInterface>(LockedTarget))
	{
		if (bLocking)
			LockOnTargetInterface->ShowInbodyCursor();
		else
			LockOnTargetInterface->HideInbodyCursor();
	}
}

void URMLockOnSystemComponent::ChangeTarget(int32 Direction)
{
	if (!IsValidTarget(CurrentTargetIndex)) return;

	int32 TargetIndex = (CurrentTargetIndex + Direction + DetectedTargetsWithDistance.Num()) % DetectedTargetsWithDistance.Num();
	if (!IsValidTarget(TargetIndex)) return;

	ARMCharacterBase* NewTarget = DetectedTargetsWithDistance[TargetIndex].Target;
	if (IsValid(LockedTarget) && IsValid(NewTarget))
	{
		HandleTargetLock(false);

		CurrentTargetIndex = TargetIndex;
		LockedTarget = NewTarget;
		HandleTargetLock(true);
	}
}

void URMLockOnSystemComponent::AdjustCameraRotation(float DeltaTime, const FVector& Direction, AActor* Owner)
{
	APawn* OwnerPawn = Cast<APawn>(Owner);
	if (OwnerPawn && OwnerPawn->IsPlayerControlled())
	{
		APlayerController* PC = Cast<APlayerController>(OwnerPawn->GetController());
		if (PC)
		{
			FRotator CurrentControlRotation = PC->GetControlRotation();

			const float AngleDifference = FMath::Abs(FMath::Acos(FVector::DotProduct(Direction, Owner->GetActorForwardVector())));
			float DynamicRotationSpeed = FMath::Lerp(MinRotationSpeed, MaxRotationSpeed, AngleDifference / 180.0f);

			FRotator TargetYawRotation(0.f, Direction.Rotation().Yaw, 0.f);
			FRotator CurrentYawRotation(0.f, CurrentControlRotation.Yaw, 0.f);
			FRotator TargetPitchRotation(Direction.Rotation().Pitch, 0.f, 0.f);
			FRotator CurrentPitchRotation(CurrentControlRotation.Pitch, 0.f, 0.f);

			float InterpedYaw = FMath::RInterpTo(CurrentYawRotation, TargetYawRotation, DeltaTime, DynamicRotationSpeed).Yaw;
			float InterpedPitch = FMath::RInterpTo(CurrentPitchRotation, TargetPitchRotation, DeltaTime, DynamicRotationSpeed).Pitch;

			FRotator NewCameraRotation = FRotator(InterpedPitch, InterpedYaw, CurrentControlRotation.Roll);
			PC->SetControlRotation(NewCameraRotation);
		}
	}
}