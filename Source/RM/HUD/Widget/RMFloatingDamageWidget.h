// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMFloatingDamageWidget.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMFloatingDamageWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeOnInitialized() override;
	
	void SetDamageText(float InDamage);

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TXT_FloatingDamage;
	
};
