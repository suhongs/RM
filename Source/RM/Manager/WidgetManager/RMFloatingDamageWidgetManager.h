// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/RMWidgetManagerBase.h"
#include "RMFloatingDamageWidgetManager.generated.h"

/**
 * 
 */

class URMObjectPool;
class ARMCharacterBase;
class ARMPooledActorBase;

UCLASS()
class RM_API URMFloatingDamageWidgetManager : public URMWidgetManagerBase
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget() override;

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;
	virtual void BindCallbacksToDependencies(ARMCharacterBase* InCharacter);

public:
	void DisplayFloatingDamage(const struct FOnAttributeChangeData& Data);
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class ARMPooledActorBase> FloatingWidgetClass;

	//WidgetPool
	UPROPERTY()
	TObjectPtr<URMObjectPool> WidgetPool;
};
