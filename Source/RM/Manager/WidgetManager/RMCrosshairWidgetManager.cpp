// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/WidgetManager/RMCrosshairWidgetManager.h"
#include "Character/RMPlayerCharacter.h"
#include "CombatSystem/RMAimComponent.h"

void URMCrosshairWidgetManager::InitWidget()
{
	Super::InitWidget();

	BindCallbacksToDependencies();
	BroadcastInitialValues();
}

void URMCrosshairWidgetManager::BroadcastInitialValues()
{
	Super::HideWidget();
}

void URMCrosshairWidgetManager::BindCallbacksToDependencies()
{
	if (Pawn == nullptr)
	{
		return;
	}

	if (ARMPlayerCharacter* PlayerCharacter = Cast<ARMPlayerCharacter>(Pawn))
	{
		if (URMAimComponent* AimComponent = PlayerCharacter->GetAimComponent())
		{
			AimComponent->OnEnterAimMode.AddUObject(this, &URMCrosshairWidgetManager::ShowWidget);
			AimComponent->OnExitAimMode.AddUObject(this, &URMCrosshairWidgetManager::HideWidget);
		}
	}
	
}
