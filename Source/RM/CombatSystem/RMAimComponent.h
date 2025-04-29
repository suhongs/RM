// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RMAimComponent.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ARMPlayerCharacter;

DECLARE_MULTICAST_DELEGATE(FOnEnterAimModeDelegate);
DECLARE_MULTICAST_DELEGATE(FOnExitAimModeDelegate);

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
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY()
	ARMPlayerCharacter* OwnerCharacter;

	UPROPERTY()
	USpringArmComponent* CameraBoom;

	UPROPERTY()
	UCameraComponent* FollowCamera;

	// === 에임 상태 값 ===
	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	FVector AimOffset = FVector(-100.f, 75.f, 80.f);

	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	float AimTargetArmLength = 200.f;

	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	float AimCameraFOV = 60.f;

	UPROPERTY(EditAnywhere, Category = "AimMode|Camera")
	float NormalCameraFOV = 90.f;

	UPROPERTY(EditAnywhere, Category = "AimMode|Smooth")
	float InterpSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category = "AimMode|Smooth")
	float FOVInterpSpeed = 10.f;

	UPROPERTY()
	bool bIsAiming = false;

	UPROPERTY()
	bool bWantsToAim = false;

	FVector DefaultCameraBoomLocation;
	float DefaultTargetArmLength;

	// 타겟값 저장용
	FVector TargetSocketOffset;
	float TargetArmLength;
	float TargetFOV;

public:
	FOnEnterAimModeDelegate OnEnterAimMode;
	FOnExitAimModeDelegate OnExitAimMode;		
};
