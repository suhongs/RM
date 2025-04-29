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

	PrimaryComponentTick.bCanEverTick = true;
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

void URMFloatingHpBarWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorld* World = GetWorld();
	if (World == nullptr)
		return;

	APlayerController* PC = World->GetFirstPlayerController();
	if (PC == nullptr)
		return;


	// Get the player's camera manager
	APlayerCameraManager* CameraManager = PC->PlayerCameraManager;
	if (!CameraManager)
	{
		return;
	}

	// Get the camera's location
	FVector CameraLocation = CameraManager->GetCameraLocation();

	// Get the widget's location (this should be the location of the actor or component it's attached to)
	FVector WidgetLocation = GetOwner()->GetActorLocation();

	// Calculate the direction vector from the widget to the camera
	FVector DirectionToCamera = CameraLocation - WidgetLocation;

	// Normalize the direction vector
	DirectionToCamera.Normalize();

	// Calculate the new rotation
	FRotator NewRotation = DirectionToCamera.Rotation();

	// Set the widget's rotation to always face the camera
	SetWorldRotation(NewRotation);
}
