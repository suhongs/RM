// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/RMPlayerState.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "Subsystem/HitProcessingSubsystem.h"


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

	TArray<UStaticMeshComponent*> StaticMeshComponents;
	GetComponents<UStaticMeshComponent>(StaticMeshComponents);
	UStaticMeshComponent* Spear = nullptr;

	// StaticMeshComponent 배열에서 Spear 찾기
	for (UStaticMeshComponent* Component : StaticMeshComponents)
	{
		if (Component && Component->GetName() == TEXT("Spear"))
		{
			UE_LOG(LogTemp, Warning, TEXT("Spear found!"));
			Spear = Component;
			break;
		}
	}


	if (Spear == nullptr)
		return;

	FVector Start = Spear->GetSocketLocation("Start");
	FVector End = Spear->GetSocketLocation("End");
	float SphereRadius = 15.0f; // 구체의 반경

	// 충돌 결과를 저장할 HitResult
	FHitResult HitResult;

	// 트레이스에 사용할 쿼리 파라미터
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // 자기 자신을 무시

	// 충돌 형태 설정 (Sphere)
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(SphereRadius);

	// 검사할 객체 타입 설정 (Pawn만 검사)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		this,                               // 월드 컨텍스트 객체
		Start,                              // 트레이스 시작 지점
		End,                                // 트레이스 끝 지점
		SphereRadius,                       // 트레이스 구체의 반경
		ObjectTypes,                        // 검사할 객체 타입
		false,                              // 복잡한 충돌을 검사하지 않음
		TArray<AActor*>(),                  // 무시할 액터들
		EDrawDebugTrace::ForDuration,       // 디버깅용으로 일정 시간 동안 트레이스를 그리기
		HitResult,                          // 충돌 결과 저장
		true,                               // 자기 자신 무시
		FLinearColor::Red,                  // 트레이스 색상
		FLinearColor::Green,                // 충돌 색상
		2.0f                                // 디버그 표시 시간
	);

	UHitProcessingSubsystem* HitProcessingSubsystem = GetGameInstance()->GetSubsystem<UHitProcessingSubsystem>();
	if (HitProcessingSubsystem == nullptr)
		return;

	if (bHit && HitResult.GetActor() != nullptr)
	{
		AActor* HitActor = HitResult.GetActor();
		ARMCharacterBase* HitCharacter = Cast<ARMCharacterBase>(HitActor);

		IRMCombatInterface* CombatInterface = Cast<IRMCombatInterface>(HitActor);

		if (HitCharacter && CombatInterface && !HitActors.Contains(HitActor))
		{
			// 충돌된 적을 목록에 추가하고, 대미지 입히기
			HitActors.Add(HitActor);

			HitProcessingSubsystem->ProcessHit(this, HitCharacter, InSkillId);

			CombatInterface->HitReact();
		}
	}
}

void ARMPlayerCharacter::HitReact()
{
	Super::HitReact();
}

void ARMPlayerCharacter::RotateCharacterToCameraYaw()
{
	if (Controller)
	{
		// 카메라 방향 기준으로 캐릭터 회전
		const FRotator ControlRot = Controller->GetControlRotation();
		const FRotator NewYawRot(0.f, ControlRot.Yaw, 0.f); // Pitch, Roll 제거하고 Yaw만 사용
		SetActorRotation(NewYawRot); // 이걸로 공격 방향이 카메라 방향이 됨
	}
}
