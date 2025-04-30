// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/RMFloatingDamage.h"
#include "HUD/Widget/RMFloatingDamageWidget.h"
#include "Components/WidgetComponent.h"

// Sets default values
ARMFloatingDamage::ARMFloatingDamage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("FloatingDamageWidgetComponent"));
}

// Called when the game starts or when spawned
void ARMFloatingDamage::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARMFloatingDamage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TotalPlayTime <= 0)
		return;

	if (CurrentPlayTime >= TotalPlayTime)
	{
		ResetObject();

		return;
	}

	UpdateWidgetLocation(DeltaTime);
	CurrentPlayTime += DeltaTime;

}

void ARMFloatingDamage::SetDamageText(float InDamage)
{
	if (IsValid(WidgetComponent))
	{
		if (URMFloatingDamageWidget* Widget = Cast<URMFloatingDamageWidget>(WidgetComponent->GetWidget()))
		{
			Widget->SetDamageText(InDamage);
		}
	}
}

void ARMFloatingDamage::StartWidgetAnimation()
{
	if (IsValid(WidgetComponent))
	{
		if (URMFloatingDamageWidget* Widget = Cast<URMFloatingDamageWidget>(WidgetComponent->GetWidget()))
		{
			//Widget->StartAnimation();
		}
	}
}

void ARMFloatingDamage::InitObject()
{
	if (!IsValid(WidgetComponent))
		return;

	WidgetComponent->SetWidgetClass(FloatingWidgetClass);
	WidgetComponent->InitWidget();
	WidgetComponent->SetVisibility(true);
	WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetComponent->GetWidget()->SetVisibility(ESlateVisibility::Visible);
}

void ARMFloatingDamage::ResetObject()
{
	CurrentPlayTime = 0;
}

void ARMFloatingDamage::UpdateWidgetLocation(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector NewLocation = CurrentLocation + (GetActorUpVector() * FloatingSpeed * DeltaTime);
	SetActorLocation(NewLocation);
}

void ARMFloatingDamage::StartFloating(FVector3d StartPosition)
{
	ResetObject();

	SetActorLocation(StartPosition);
}

