// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual void NativeOnInitialized() override;

	void SetHealth(float Current, float Max);
	void SetMana(float Current, float Max);

public:

	// 체력/마나 ProgressBar
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_Health;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> PB_Mana;

	// 체력/마나 TextBlock
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> TXT_Health;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<class UTextBlock> TXT_Mana;

};
