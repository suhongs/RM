// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/RMPlayerController.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Character/RMCharacterBase.h"
#include "Character/RMPlayerCharacter.h"
#include "AbilitySystemComponent.h"
#include "CombatSystem/RMAimComponent.h"
#include "HUD/RMHUD.h"

ARMPlayerController::ARMPlayerController()
{

}

void ARMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	ARMCharacterBase* PawnCharacter = GetPawn<ARMCharacterBase>();

	if (PawnCharacter)
	{
		AbilitySystemComponent = PawnCharacter->AbilitySystemComponent;
	}


	ARMHUD* HUD = GetHUD<ARMHUD>();
	if (IsValid(HUD))
	{
		HUD->InitHUD(this, GetPlayerState<APlayerState>(), PawnCharacter, AbilitySystemComponent);
	}
}

void ARMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	if (EnhancedInputComponent)
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ARMPlayerController::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ARMPlayerController::StopJump);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ARMPlayerController::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ARMPlayerController::Look);

		// Combat
		EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Started, this, &ARMPlayerController::LightAttack);
		EnhancedInputComponent->BindAction(HeavyAttackAction, ETriggerEvent::Started, this, &ARMPlayerController::HeavyAttack);

		// Utilities
		EnhancedInputComponent->BindAction(RollAction, ETriggerEvent::Started, this, &ARMPlayerController::Roll);
		EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Started, this, &ARMPlayerController::Dodge);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Started, this, &ARMPlayerController::Aim);


	}
}

UAbilitySystemComponent* ARMPlayerController::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ARMPlayerController::Move(const FInputActionValue& Value)
{
	ARMCharacterBase* ControlledCharacter = Cast<ARMCharacterBase>(GetPawn());

	if (ControlledCharacter == nullptr)
		return;

	MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	ControlledCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
	ControlledCharacter->AddMovementInput(RightDirection, MovementVector.X);
}

void ARMPlayerController::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddYawInput(LookAxisVector.X * this->LookSensitivity);
	AddPitchInput(LookAxisVector.Y * this->LookSensitivity);
}

void ARMPlayerController::Jump(const FInputActionValue& Value)
{
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	FGameplayTag JumpTag = FGameplayTag::RequestGameplayTag(FName("Player.Utilities.Jump"));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(JumpTag);

	bool result = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void ARMPlayerController::StopJump(const FInputActionValue& Value)
{
	ARMCharacterBase* ControlledCharacter = Cast<ARMCharacterBase>(GetPawn());

	if (ControlledCharacter == nullptr)
		return;

	ControlledCharacter->StopJumping();
}

void ARMPlayerController::LightAttack()
{
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	FGameplayTag LightAttackTag = FGameplayTag::RequestGameplayTag(FName("Player.Attack.LightAttack"));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(LightAttackTag);

	bool result = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void ARMPlayerController::HeavyAttack()
{
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	FGameplayTag HeavyAttackTag = FGameplayTag::RequestGameplayTag(FName("Player.Attack.HeavyAttack"));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(HeavyAttackTag);

	bool bActivated = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);

	if (!bActivated)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to activate HeavyAttack ability"));
	}
}

void ARMPlayerController::Roll()
{
	ARMCharacterBase* ControlledCharacter = Cast<ARMCharacterBase>(GetPawn());
	if (!IsValid(ControlledCharacter))
		return;;

	// 기본적으로 Roll은 캐릭터가 바라보는 방향으로 진행
	FVector RollDirection = ControlledCharacter->GetActorForwardVector(); // 캐릭터가 바라보는 방향


	if (MovementVector.SizeSquared() > 0) // 입력이 있다면
	{
		// 방향키 입력이 있으면 해당 방향으로 롤
		const FRotator Rotation = GetControlRotation(); // 컨트롤러의 회전 값
		const FRotator YawRotation(0, Rotation.Yaw, 0); // Yaw만 고려하여 회전 방향 설정

		// 입력된 방향 벡터 계산
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// MoveDirection은 상대적으로 X와 Y 축 방향이므로, 이를 X와 Y 축으로 나누어 각각 처리
		RollDirection = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;

		// 입력된 방향을 향해 회전
		FRotator NewRotation = RollDirection.Rotation(); // 롤 방향에 맞게 회전 계산
		ControlledCharacter->SetActorRotation(NewRotation); // 새로운 회전 값 적용
	}

	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	FGameplayTag JumpTag = FGameplayTag::RequestGameplayTag(FName("Player.Utilities.Roll"));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(JumpTag);

	bool result = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);

}

void ARMPlayerController::Dodge()
{
	ARMCharacterBase* ControlledCharacter = Cast<ARMCharacterBase>(GetPawn());
	if (!IsValid(ControlledCharacter))
		return;

	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	// 기본값은 캐릭터가 보고 있는 방향
	FVector DodgeDirection = ControlledCharacter->GetActorForwardVector();
	FRotator ControlRot = GetControlRotation();

	FString DirectionTagStr = TEXT("None");

	if (MovementVector.SizeSquared() > 0)
	{
		// 카메라 Yaw만 사용해서 Forward/Right 방향 구함
		const FRotator YawRotation(0, ControlRot.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 입력 방향 (MovementVector) + 카메라 기준 방향 → 최종 대시 방향
		DodgeDirection = ForwardDirection * MovementVector.Y + RightDirection * MovementVector.X;

		// 방향 판별은 캐릭터 기준으로 계산
		FVector DodgeDirNormalized = DodgeDirection.GetSafeNormal();
		float ForwardDot = FVector::DotProduct(DodgeDirNormalized, ControlledCharacter->GetActorForwardVector());
		float RightDot = FVector::DotProduct(DodgeDirNormalized, ControlledCharacter->GetActorRightVector());

		if (FMath::Abs(ForwardDot) > FMath::Abs(RightDot))
		{
			DirectionTagStr = ForwardDot > 0 ? TEXT("FW") : TEXT("BW");
		}
		else
		{
			DirectionTagStr = RightDot > 0 ? TEXT("R") : TEXT("L");
		}
	}
	else
	{
		// 입력이 없으면 바라보는 방향 기준으로 전방 대시
		DirectionTagStr = TEXT("FW");
	}

	// 태그 생성 및 어빌리티 활성화
	FString FullTagName = FString::Printf(TEXT("Player.Utilities.Dodge.%s"), *DirectionTagStr);
	FGameplayTag DodgeTag = FGameplayTag::RequestGameplayTag(FName(*FullTagName));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(DodgeTag);

	bool bSuccess = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void ARMPlayerController::Aim()
{
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	FGameplayTag ModeTag = FGameplayTag::RequestGameplayTag(FName("Player.Mode"));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(ModeTag);

	bool result = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);


	ARMPlayerCharacter* ControlledCharacter = Cast<ARMPlayerCharacter>(GetPawn());
	if (result && !IsValid(ControlledCharacter))
		return;

	if (URMAimComponent* AimComponent = ControlledCharacter->GetAimComponent())
	{
		if (AimComponent->IsAiming())
		{

			AimComponent->ExitAimMode();
		}
		else
		{
			AimComponent->EnterAimMode();
		}
	}
}
