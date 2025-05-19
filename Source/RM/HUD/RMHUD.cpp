// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RMHUD.h"
#include "Blueprint/UserWidget.h"
#include "Manager/WidgetManager/RMHUDWidgetManager.h"
#include "Manager/WidgetManager/RMCrosshairWidgetManager.h"
#include "Manager/WidgetManager/RMFloatingDamageWidgetManager.h"

void ARMHUD::BeginPlay()
{
	Super::BeginPlay();

}

void ARMHUD::InitHUD(APlayerController* InPC, APlayerState* InPS, ARMCharacterBase* InActor, UAbilitySystemComponent* InAbilitySystemComponent)
{
	const FRMWidgetManagerParams WidgetManagerParams(InPC, InPS, InActor, InAbilitySystemComponent);

	if (HUDWidgetManagerClass)
	{
		HUDWidgetManager = NewObject<URMHUDWidgetManager>(this, HUDWidgetManagerClass);
		HUDWidgetManager->SetWidgetManagerParams(WidgetManagerParams);
		HUDWidgetManager->InitWidget();
	}

	if (CrosshairWidgetManagerClass)
	{
		CrosshairWidgetManager = NewObject<URMCrosshairWidgetManager>(this, CrosshairWidgetManagerClass);
		CrosshairWidgetManager->SetWidgetManagerParams(WidgetManagerParams);
		CrosshairWidgetManager->InitWidget();
	}

	if (FloatingDamageWidgetManagerClass)
	{
		FloatingDamageWidgetManager = NewObject<URMFloatingDamageWidgetManager>(this, FloatingDamageWidgetManagerClass);
		FloatingDamageWidgetManager->SetWidgetManagerParams(WidgetManagerParams);
		FloatingDamageWidgetManager->InitWidget();
	}
}
