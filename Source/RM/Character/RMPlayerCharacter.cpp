// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/RMPlayerState.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "Subsystem/HitProcessingSubsystem.h"
#include "CombatSystem/RMLockOnSystemComponent.h"

#include "Projectile/RMProjectileBase.h"

// For Debug
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

ARMPlayerCharacter::ARMPlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("PlayerCameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 100.f);
	CameraBoom->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerFollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	AimComponent = CreateDefaultSubobject<URMAimComponent>(TEXT("AimComponent"));
}

void ARMPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	InitDefaultAbility();
	Super::InitDefaultAttributes();
}

void ARMPlayerCharacter::InitAbilityActorInfo()
{
	ARMPlayerState* PS = GetPlayerState<ARMPlayerState>();
	if (!IsValid(PS))
		return;

	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	if (AbilitySystemComponent == nullptr)
		return;

	AttributeSet = PS->GetAttributeSet();

	AbilitySystemComponent->InitAbilityActorInfo(PS, this);
}

void ARMPlayerCharacter::HitDetection(const FRMSkillId& InSkillId)
{
	Super::HitDetection(InSkillId);
}

void ARMPlayerCharacter::HitReact()
{
	Super::HitReact();
}

void ARMPlayerCharacter::ThrowSpear()
{
	TArray<USceneComponent*> SceneComponents;
	GetComponents<USceneComponent>(SceneComponents);
	USceneComponent* Weapon = nullptr;

	for (USceneComponent* Component : SceneComponents)
	{
		if (Component && Component->GetName() == TEXT("Weapon"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Weapon found!"));
			Weapon = Component;
			break;
		}
	}

	if (!ProjectileClass || !Weapon)
	{
		UE_LOG(LogTemp, Warning, TEXT("ProjectileClass or Weapon is missing!"));
		return;
	}

	// 카메라 기준 라인트레이스 (크로스헤어 방향)
	FVector TraceStart = FollowCamera->GetComponentLocation();
	FVector TraceDirection = FollowCamera->GetForwardVector();
	FVector TraceEnd = TraceStart + TraceDirection * 10000.f;

	FHitResult Hit;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit, TraceStart, TraceEnd, ECC_Visibility, Params
	);

	FVector TargetLocation = bHit ? Hit.ImpactPoint : TraceEnd;

	// 크로스헤어 방향으로 던지기 위한 방향
	FVector AimDirection = (TargetLocation - TraceStart).GetSafeNormal();
	FRotator ProjectileRotation = AimDirection.Rotation();

	// 스폰 위치는 Weapon 위치
	FVector SpawnLocation = Weapon->GetComponentLocation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// 투사체 생성
	ARMProjectileBase* Projectile = GetWorld()->SpawnActor<ARMProjectileBase>(
		ProjectileClass,
		SpawnLocation,
		ProjectileRotation,
		SpawnParams
	);

	if (Projectile)
	{
		Projectile->InitProjectile(this, 3);
		Projectile->InitVelocity(AimDirection);
	}

}

void ARMPlayerCharacter::RotateCharacterToCameraYaw()
{
	if (!IsValid(LockOnSystemComponent))
		return;

	if (LockOnSystemComponent->IsLockedOn() && LockOnSystemComponent->LockedTarget)
	{
		const FVector Direction = (LockOnSystemComponent->LockedTarget->GetActorLocation() - Owner->GetActorLocation()).GetSafeNormal();
		FRotator CurrentRotation = Owner->GetActorRotation();
		float TargetYaw = Direction.Rotation().Yaw;
		FRotator NewRotation(CurrentRotation.Pitch, TargetYaw, CurrentRotation.Roll);
	}
}
