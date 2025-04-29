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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<URMFloatingHpBarWidget> FloatingWidgetClass;

	UPROPERTY()
	TObjectPtr<URMFloatingHpBarWidget> FloatingWidget;
};
