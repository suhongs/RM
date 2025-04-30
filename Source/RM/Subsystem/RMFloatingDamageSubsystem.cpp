// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RMFloatingDamageSubsystem.h"
#include "ObjectPool/RMObjectPool.h"
#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"
#include "HUD/RMFloatingDamage.h"
#include "GameplayEffectExtension.h"
#include "Components/WidgetComponent.h"

URMFloatingDamageSubsystem::URMFloatingDamageSubsystem()
{
	static ConstructorHelpers::FClassFinder<ARMPooledActorBase> DamageActorBPClass(TEXT("/Game/UI/FloatingDamage/BP_FloatingDamageActor"));

	if (DamageActorBPClass.Succeeded())
	{
		FloatingDamageActorClass = DamageActorBPClass.Class;
	}

}

void URMFloatingDamageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	WidgetPool = NewObject<URMObjectPool>(GetWorld(), TEXT("WidgetPool"));

	
	WidgetPool->InitializePool(FloatingDamageActorClass);
}

void URMFloatingDamageSubsystem::RegisterWithAbilitySystem(ARMCharacterBase* InCharacter)
{
	if (!IsValid(InCharacter))
		return;

	UAbilitySystemComponent* TargetAbilitySystemComponent = InCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
		return;

	URMAttributeSet* TargetAttributeSet = InCharacter->GetAttributeSet();
	if (!IsValid(TargetAttributeSet))
		return;

	TargetAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &URMFloatingDamageSubsystem::DisplayFloatingDamage);
}

void URMFloatingDamageSubsystem::DisplayFloatingDamage(const FOnAttributeChangeData& Data)
{
	float FinalDamage = Data.OldValue - Data.NewValue;

	ARMFloatingDamage* FloatingDamageActor = Cast<ARMFloatingDamage>(WidgetPool->RequestObject(GetWorld()));

	if (IsValid(FloatingDamageActor))
	{
		UAbilitySystemComponent& TargetAbiltySystemComponent = Data.GEModData->Target;

		AActor* TargetActor = TargetAbiltySystemComponent.GetOwnerActor();
		if (!IsValid(TargetActor))
			return;

		FVector DamageLocation = TargetActor->GetActorLocation();
		float OffsetX = FMath::FRandRange(-10.f, 10.f);
		float OffsetY = FMath::FRandRange(-10.f, 10.f);
		float OffsetZ = FMath::FRandRange(0.f, 20.f);  // Z는 위로만 띄우고 싶으면 0~20

		FVector RandomOffset(OffsetX, OffsetY, OffsetZ);
		DamageLocation += RandomOffset;

		FloatingDamageActor->SetDamageText(FinalDamage);

		UWidgetComponent* WidgetComponent = FloatingDamageActor->FindComponentByClass<UWidgetComponent>();

		if (IsValid(WidgetComponent))
		{
			UUserWidget* FloatingWidget = WidgetComponent->GetWidget();
			if (IsValid(FloatingWidget))
			{
				FloatingWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
			}

			FloatingDamageActor->StartFloating(DamageLocation);

			if (UWorld* World = FloatingDamageActor->GetWorld())
			{
				FTimerManager& TimerManager = World->GetTimerManager();
				FTimerHandle TimerHandle;

				TWeakObjectPtr<ARMFloatingDamage> WeakFloatingActor = MakeWeakObjectPtr(FloatingDamageActor);
				TWeakObjectPtr<UWidgetComponent> WeakComponent = MakeWeakObjectPtr(WidgetComponent);
				TWeakObjectPtr<URMFloatingDamageSubsystem> WeakThis = MakeWeakObjectPtr(this);

				TimerManager.SetTimer(TimerHandle, [WeakFloatingActor, WeakComponent, WeakThis]()
					{
						if (WeakThis.IsValid() == false)
							return;

						if (WeakFloatingActor.IsValid() == false)
							return;

						if (WeakComponent.IsValid() == false)
							return;

						WeakComponent->GetWidget()->SetVisibility(ESlateVisibility::Collapsed);
						WeakThis->WidgetPool->ReturnObject(WeakFloatingActor.Get());

					}, FloatingDamageActor->TotalPlayTime, false);
			}
		}
	}
}
