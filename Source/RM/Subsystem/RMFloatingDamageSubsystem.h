// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RMFloatingDamageSubsystem.generated.h"

/**
 * 
 */
class URMObjectPool;
class ARMCharacterBase;
UCLASS()
class RM_API URMFloatingDamageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	

public:
	URMFloatingDamageSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:

	void RegisterWithAbilitySystem(ARMCharacterBase* InCharacter);

	void DisplayFloatingDamage(const struct FOnAttributeChangeData& Data);


private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARMPooledActorBase> FloatingDamageActorClass;

	//WidgetPool
	UPROPERTY()
	TObjectPtr<URMObjectPool> WidgetPool;
	
};
