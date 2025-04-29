// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"
#include "AbilitySystem/GameplayEffect/RMGameplayEffectBase.h"

#include "Subsystem/HitProcessingSubsystem.h"

// For Debug
#include "DrawDebugHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ARMCharacterBase::ARMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LockOnSystemComponent = CreateDefaultSubobject<URMLockOnSystemComponent>(TEXT("LockOnComponent"));
}

// Called when the game starts or when spawned
void ARMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARMCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ARMCharacterBase::InitAbilityActorInfo()
{

}

void ARMCharacterBase::InitDefaultAbility()
{
	if (IsValid(AbilitySystemComponent) == false)
		return;

	for (auto Ability : DefaultAbilities)
	{
		if (IsValid(Ability) == false)
			continue;

		AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, 0, 0, this));
	}
}

// Called every frame
void ARMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ARMCharacterBase::InitDefaultAttributes()
{
	if (AbilitySystemComponent && DefaultStatEffect)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultStatEffect, 1.0f, EffectContext);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ARMCharacterBase::HitDetection(const FRMSkillId& InSkillId)
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

	/*
		Start			: ������ ������ �κ� ��ġ
		End				: ������ �� �� �κ� ��ġ
		SphereRaduis	: SphereTrace�� �ݰ�
	*/

	FVector Start = Spear->GetSocketLocation("Start");
	FVector End = Spear->GetSocketLocation("End");
	float SphereRadius = 15.0f; 

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

	/*
		HitResult���� �浹�� ���� Ÿ���� Ȯ�� ��
		��ȿ�� Target���� �������� ������,
		�Ѹ��� ���� �ߺ����� �������� �޴°��� �����ϱ� ���� HitActors�� ����
	*/

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

void ARMCharacterBase::HitReact()
{
	if (AbilitySystemComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AbilitySystemComponent is nullptr"));
		return;
	}

	FGameplayTag HitReactTag = FGameplayTag::RequestGameplayTag(FName("Common.Combat.HitReact"));

	FGameplayTagContainer TagContainer;
	TagContainer.AddTag(HitReactTag);

	bool result = AbilitySystemComponent->TryActivateAbilitiesByTag(TagContainer);
}

void ARMCharacterBase::ClearHitActors()
{
	HitActors.Empty();
}

UAbilitySystemComponent* ARMCharacterBase::GetAbilitySystemComponent() const
{
	return this->AbilitySystemComponent;
}

