// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatSystem/RMAimComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/RMPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

URMAimComponent::URMAimComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
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
}

void URMAimComponent::EnterAimMode()
{
	if (!CameraBoom || !FollowCamera || bIsAiming)
		return;

	if (!IsValid(OwnerCharacter))
	{
		return;
	}

	AlignToCamera(true);

	bIsAiming = true;

	// 카메라 설정 변경
	CameraBoom->SocketOffset = AimOffset;
	CameraBoom->TargetArmLength = AimTargetArmLength;
	FollowCamera->SetFieldOfView(AimCameraFOV);

	// TODO: 에임 UI On
}

void URMAimComponent::ExitAimMode()
{
	if (!CameraBoom || !FollowCamera || !bIsAiming)
		return;

	AlignToCamera(false);
	bIsAiming = false;

	// 원래대로 복귀
	CameraBoom->SocketOffset = DefaultCameraBoomLocation;
	CameraBoom->TargetArmLength = DefaultTargetArmLength;
	FollowCamera->SetFieldOfView(NormalCameraFOV);

	// TODO: 에임 UI Off
}

void URMAimComponent::AlignToCamera(bool InIsAlign)
{
	if (!IsValid(OwnerCharacter))
	{
		return;
	}

	if (UCharacterMovementComponent* MovementComponent = OwnerCharacter->GetCharacterMovement())
	{
		if (InIsAlign)
		{
			MovementComponent->MaxWalkSpeed = 200;
		}
		else
		{
			MovementComponent->MaxWalkSpeed = 600;
		}

		OwnerCharacter->bUseControllerRotationYaw = InIsAlign;
		MovementComponent->bOrientRotationToMovement = !InIsAlign;
	}
}
