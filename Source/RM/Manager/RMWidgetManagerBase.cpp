// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/RMWidgetManagerBase.h"
#include "RMWidgetManagerBase.h"
#include "Blueprint/UserWidget.h"

void URMWidgetManagerBase::InitWidget()
{
	CreateAndAddWidget();
	ShowWidget();
}

void URMWidgetManagerBase::CreateAndAddWidget()
{
	if (WidgetClass != nullptr)
	{
		Widget = CreateWidgetInternal();

		if (IsValid(Widget) == true)
		{
			Widget->AddToViewport();
		}
	}
}

void URMWidgetManagerBase::RemoveWidget()
{
	if (Widget != nullptr && Widget->IsInViewport())
	{
		Widget->RemoveFromParent();
		Widget = nullptr;
	}
}

void URMWidgetManagerBase::ShowWidget()
{
	SetWidgetVisibility(ESlateVisibility::Visible);
}

void URMWidgetManagerBase::HideWidget()
{
	SetWidgetVisibility(ESlateVisibility::Collapsed);
}

void URMWidgetManagerBase::SetWidgetVisibility(ESlateVisibility NewVisibility)
{
	if (Widget)
	{
		Widget->SetVisibility(NewVisibility);
	}
}

bool URMWidgetManagerBase::IsWidgetValid() const
{
	return IsValid(Widget);
}

UUserWidget* URMWidgetManagerBase::CreateWidgetInternal()
{

	if (WidgetClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("WidgetClass is null in %s"), *GetNameSafe(this));
		return nullptr;
	}

	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController is null in %s"), *GetNameSafe(this));
		return nullptr;
	}

	if (PlayerController->GetWorld() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("GetWorld() is null in PlayerController: %s (in %s)"),
			*GetNameSafe(PlayerController), *GetNameSafe(this));
		return nullptr;
	}

	return CreateWidget<UUserWidget>(PlayerController, WidgetClass);
}

void URMWidgetManagerBase::SetWidgetManagerParams(const FRMWidgetManagerParams& WMParams)
{
	PlayerController = WMParams.PlayerController;
	PlayerState = WMParams.PlayerState;
	Pawn = WMParams.Pawn;
	AbilitySystemComponent = WMParams.AbilitySystemComponent;
}

void URMWidgetManagerBase::BroadcastInitialValues()
{
}

void URMWidgetManagerBase::BindCallbacksToDependencies()
{
}
