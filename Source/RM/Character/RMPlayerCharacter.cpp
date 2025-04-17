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

	// StaticMeshComponent �迭���� Spear ã��
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
	float SphereRadius = 15.0f; // ��ü�� �ݰ�

	// �浹 ����� ������ HitResult
	FHitResult HitResult;

	// Ʈ���̽��� ����� ���� �Ķ����
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // �ڱ� �ڽ��� ����

	// �浹 ���� ���� (Sphere)
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(SphereRadius);

	// �˻��� ��ü Ÿ�� ���� (Pawn�� �˻�)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));

	bool bHit = UKismetSystemLibrary::SphereTraceSingleForObjects(
		this,                               // ���� ���ؽ�Ʈ ��ü
		Start,                              // Ʈ���̽� ���� ����
		End,                                // Ʈ���̽� �� ����
		SphereRadius,                       // Ʈ���̽� ��ü�� �ݰ�
		ObjectTypes,                        // �˻��� ��ü Ÿ��
		false,                              // ������ �浹�� �˻����� ����
		TArray<AActor*>(),                  // ������ ���͵�
		EDrawDebugTrace::ForDuration,       // ���������� ���� �ð� ���� Ʈ���̽��� �׸���
		HitResult,                          // �浹 ��� ����
		true,                               // �ڱ� �ڽ� ����
		FLinearColor::Red,                  // Ʈ���̽� ����
		FLinearColor::Green,                // �浹 ����
		2.0f                                // ����� ǥ�� �ð�
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
			// �浹�� ���� ��Ͽ� �߰��ϰ�, ����� ������
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
		// ī�޶� ���� �������� ĳ���� ȸ��
		const FRotator ControlRot = Controller->GetControlRotation();
		const FRotator NewYawRot(0.f, ControlRot.Yaw, 0.f); // Pitch, Roll �����ϰ� Yaw�� ���
		SetActorRotation(NewYawRot); // �̰ɷ� ���� ������ ī�޶� ������ ��
	}
}
