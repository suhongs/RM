// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMFloatingHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMFloatingHpBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

	void SetHealth(float Current, float Max);


public:
	// Ã¼·Â ProgressBar
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_Health;
};
