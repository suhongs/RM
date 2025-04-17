// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RMFloatingHpBarWidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "HUD/RMFloatingHpBarWidget.h"
#include "AbilitySystem/RMAttributeSet.h"

void URMFloatingHpBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(FloatingWidgetClass))
	{
		FloatingWidget = CreateWidget<URMFloatingHpBarWidget>(GetWorld(), FloatingWidgetClass);
		SetWidget(FloatingWidget);
	}

	SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	SetRelativeScale3D(FVector(1.f, 0.1f, 0.1f));
	SetWidgetSpace(EWidgetSpace::World);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetVisibility(true);
}

void URMFloatingHpBarWidgetComponent::InitFloatingWidgetComponent(URMAttributeSet* AttributeSet)
{
	if (IsValid(AttributeSet) == false)
		return;

	if (FloatingWidget == nullptr)
		return;

	AttributeSet->OnHealthChanged.AddUObject(FloatingWidget, &URMFloatingHpBarWidget::SetHealth);
	FloatingWidget->SetHealth(AttributeSet->GetCurrentHealth(), AttributeSet->GetMaxHealth());
}
