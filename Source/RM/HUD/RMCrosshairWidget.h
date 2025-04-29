// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMCrosshairWidget.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMCrosshairWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UImage* CrosshairImage;

};
