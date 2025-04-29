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

	/*
		Start			: 무기의 손잡이 부분 위치
		End				: 무기의 날 끝 부분 위치
		SphereRaduis	: SphereTrace의 반경
	*/

	FVector Start = Spear->GetSocketLocation("Start");
	FVector End = Spear->GetSocketLocation("End");
	float SphereRadius = 15.0f; 

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

	/*
		HitResult에서 충돌된 적의 타입을 확인 후
		유효한 Target에게 데미지를 입히고,
		한명의 적이 중복으로 데미지를 받는것을 방지하기 위해 HitActors에 저장
	*/

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

