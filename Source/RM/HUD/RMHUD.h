// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RMHUD.generated.h"

class UAbilitySystemComponent;
class ARMCharacterBase;
class URMWidgetManagerBase;
class URMHUDWidgetManager;

/**
 * 
 */
UCLASS()
class RM_API ARMHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	void InitHUD(APlayerController* InPC, APlayerState* InPS, ARMCharacterBase* InActor, UAbilitySystemComponent* InAbilitySystemComponent);

	template <typename T>
	T* GetWidgetManager() const
	{
		if (TIsDerivedFrom<T, URMWidgetManagerBase>::IsDerived)
		{
			for (URMWidgetManagerBase* Manager : WidgetManagers)
			{
				if (T* CastedManager = Cast<T>(Manager))
				{
					return CastedManager;
				}
			}
		}
		return nullptr;
	}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<URMWidgetManagerBase> HUDWidgetManagerClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URMWidgetManagerBase> HUDWidgetManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<URMWidgetManagerBase> CrosshairWidgetManagerClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URMWidgetManagerBase> CrosshairWidgetManager;

	UPROPERTY(EditDafaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<URMWidgetManagerBase> FloatingDamageWidgetManagerClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URMWidgetManagerBase> FloatingDamageWidgetManager;
};
