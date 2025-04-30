// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/RMWidgetManagerBase.h"
#include "GameplayEffectTypes.h"
#include "RMHUDWidgetManager.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMHUDWidgetManager : public URMWidgetManagerBase
{
	GENERATED_BODY()
	
	
public:
	virtual void InitWidget() override;

	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

public:
	void SetHealthProgressBar(const FOnAttributeChangeData& Data);
	
	void SetManaProgressBar(const FOnAttributeChangeData& Data);
};
