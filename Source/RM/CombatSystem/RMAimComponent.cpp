// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/RMAimComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/RMPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

URMAimComponent::URMAimComponent()
{
	PrimaryComponentTick.bCanEverTick = true; // Tick 활성화
}

void URMAimComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ARMPlayerCharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Error, TEXT("RMAimComponent: Invalid owner."));
		return;
	}

	CameraBoom = OwnerCharacter->FindComponentByClass<USpringArmComponent>();
	FollowCamera = OwnerCharacter->FindComponentByClass<UCameraComponent>();

	if (!CameraBoom || !FollowCamera)
	{
		UE_LOG(LogTemp, Error, TEXT("RMAimComponent: Missing CameraBoom or FollowCamera."));
		return;
	}

	DefaultCameraBoomLocation = CameraBoom->SocketOffset;
	DefaultTargetArmLength = CameraBoom->TargetArmLength;

	// 초기 목표값은 현재 값
	TargetSocketOffset = CameraBoom->SocketOffset;
	TargetArmLength = CameraBoom->TargetArmLength;
	TargetFOV = FollowCamera->FieldOfView;
}

void URMAimComponent::EnterAimMode()
{
	if (!CameraBoom || !FollowCamera)
		return;

	if (!IsValid(OwnerCharacter))
		return;

	AlignToCamera(true);
	bIsAiming = true;
	bWantsToAim = true;

	TargetSocketOffset = AimOffset;
	TargetArmLength = AimTargetArmLength;
	TargetFOV = AimCameraFOV;

	if (OnEnterAimMode.IsBound())
	{
		OnEnterAimMode.Broadcast();
	}
}

void URMAimComponent::ExitAimMode()
{
	if (!CameraBoom || !FollowCamera)
		return;

	AlignToCamera(false);
	bIsAiming = false;
	bWantsToAim = false;

	TargetSocketOffset = DefaultCameraBoomLocation;
	TargetArmLength = DefaultTargetArmLength;
	TargetFOV = NormalCameraFOV;

	if (OnExitAimMode.IsBound())
	{
		OnExitAimMode.Broadcast();
	}
}

void URMAimComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CameraBoom || !FollowCamera)
		return;

	CameraBoom->SocketOffset = FMath::VInterpTo(CameraBoom->SocketOffset, TargetSocketOffset, DeltaTime, InterpSpeed);
	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, TargetArmLength, DeltaTime, InterpSpeed);

	float CurrentFOV = FollowCamera->FieldOfView;
	float NewFOV = FMath::FInterpTo(CurrentFOV, TargetFOV, DeltaTime, FOVInterpSpeed);
	FollowCamera->SetFieldOfView(NewFOV);
}

void URMAimComponent::AlignToCamera(bool InIsAlign)
{
	if (!IsValid(OwnerCharacter))
		return;

	if (UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement())
	{
		MovementComponent->MaxWalkSpeed = InIsAlign ? 200.f : 600.f;
		OwnerCharacter->bUseControllerRotationYaw = InIsAlign;
		MovementComponent->bOrientRotationToMovement = !InIsAlign;
	}
}
