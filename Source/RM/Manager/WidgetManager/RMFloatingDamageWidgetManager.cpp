// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WidgetManager/RMFloatingDamageWidgetManager.h"
#include "objectpool/RMObjectPool.h"
#include "Character/RMCharacterBase.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "AbilitySystem/RMAttributeSet.h"
#include "HUD/RMFloatingDamage.h"
#include "GameplayEffectExtension.h"
#include "Components/WidgetComponent.h"

void URMFloatingDamageWidgetManager::InitWidget()
{
	WidgetPool = NewObject<URMObjectPool>(GetWorld(), TEXT("WidgetPool"));
	WidgetPool->InitializePool(FloatingWidgetClass);
}


void URMFloatingDamageWidgetManager::BroadcastInitialValues()
{
}

void URMFloatingDamageWidgetManager::BindCallbacksToDependencies()
{
}

void URMFloatingDamageWidgetManager::BindCallbacksToDependencies(ARMCharacterBase* InCharacter)
{
	if (!IsValid(InCharacter))
		return;

	UAbilitySystemComponent* TargetAbilitySystemComponent = InCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetAbilitySystemComponent))
		return;

	URMAttributeSet* TargetAttributeSet = InCharacter->GetAttributeSet();
	if (!IsValid(TargetAttributeSet))
		return;

	TargetAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(TargetAttributeSet->GetCurrentHealthAttribute()).AddUObject(this, &URMFloatingDamageWidgetManager::DisplayFloatingDamage);

}

void URMFloatingDamageWidgetManager::DisplayFloatingDamage(const FOnAttributeChangeData& Data)
{
	float FinalDamage = Data.OldValue - Data.NewValue;

	ARMFloatingDamage* FloatingDamageActor = Cast<ARMFloatingDamage>(WidgetPool->RequestObject(GetWorld()));
	
	if (IsValid(FloatingDamageActor))
	{
		UAbilitySystemComponent& TargetAbiltySystemComponent = Data.GEModData->Target;

		AActor* TargetActor = TargetAbiltySystemComponent.GetOwnerActor();


		FVector DamageLocation = TargetActor->GetActorLocation();
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
				TWeakObjectPtr<URMFloatingDamageWidgetManager> WeakThis = MakeWeakObjectPtr(this);

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

					}, 2.0f, false);
			}
		}
	}
}

