// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RMInbodyCursorWidgetComponent.h"
#include "HUD/RMCrosshairWidget.h"
void URMInbodyCursorWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	InitWidget();
	SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	SetWidgetSpace(EWidgetSpace::Screen);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetVisibility(false);


}

void URMInbodyCursorWidgetComponent::ShowWidget()
{

	SetVisibility(true);
}

void URMInbodyCursorWidgetComponent::HideWidget()
{

	SetVisibility(false);
}
