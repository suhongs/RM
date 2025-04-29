// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "RMInbodyCursorWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class RM_API URMInbodyCursorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:
	void ShowWidget();
	void HideWidget();
	
	
};
