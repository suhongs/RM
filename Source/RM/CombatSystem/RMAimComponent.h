// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RMAimComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ARMPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RM_API URMAimComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URMAimComponent();

	void EnterAimMode();
	void ExitAimMode();
	void AlignToCamera(bool InIsAlign);
	bool IsAiming() const { return bIsAiming; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	ARMPlayerCharacter* OwnerCharacter;

	UPROPERTY()
	USpringArmComponent* CameraBoom;

	UPROPERTY()
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	FVector AimOffset = FVector(-100.f, 75.f, 80.f);

	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	float AimTargetArmLength = 200.f;

	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	float AimCameraFOV = 60.f;

	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	float NormalCameraFOV = 90.f;

	UPROPERTY()
	bool bIsAiming = false;

	FVector DefaultCameraBoomLocation;
	float DefaultTargetArmLength;

		
};
