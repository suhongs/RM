// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "RMFloatingHpBarWidgetComponent.generated.h"

/**
 * 
 */

class URMAttributeSet;
class URMFloatingHpBarWidget;

UCLASS()
class RM_API URMFloatingHpBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void InitFloatingWidgetComponent(URMAttributeSet* AttributeSet);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<URMFloatingHpBarWidget> FloatingWidgetClass;

	TObjectPtr<URMFloatingHpBarWidget> FloatingWidget;
};
