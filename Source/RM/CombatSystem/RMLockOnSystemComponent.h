// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RMLockOnSystemComponent.generated.h"

class ARMCharacterBase;

USTRUCT(BlueprintType)
struct FLockOnTargetData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	ARMCharacterBase* Target = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float Distance = 0.f;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RM_API URMLockOnSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URMLockOnSystemComponent();

	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "LockOn")
	void LockOn();

	UFUNCTION(BlueprintCallable, Category = "LockOn")
	void Unlock();

	UFUNCTION(BlueprintCallable, Category = "LockOn")
	void FindTargetsInRange();

	UFUNCTION(BlueprintCallable, Category = "LockOn")
	void LockOnNextTarget();

	UFUNCTION(BlueprintCallable, Category = "LockOn")
	void LockOnPrevTarget();

	UFUNCTION(BlueprintPure, Category = "LockOn")
	bool IsLockedOn() const { return LockedTarget != nullptr; }


private:
	void RotateTowardTarget(float DeltaTime);

	void AdjustMovementForLockOn();

	void ResetMovementAfterUnlock();

	bool IsValidTarget(int32 Index) const;

	bool IsValidCombatTarget(ARMCharacterBase* Target) const;

	void HandleTargetLock(bool bLocking);

	void ChangeTarget(int32 Direction);

	void AdjustCameraRotation(float DeltaTime, const FVector& Direction, AActor* Owner);

public:
	UPROPERTY(BlueprintReadOnly, Category = "LockOn")
	TArray<FLockOnTargetData> DetectedTargetsWithDistance;

	UPROPERTY(BlueprintReadOnly, Category = "LockOn")
	int32 CurrentTargetIndex = 0;

	UPROPERTY(BlueprintReadOnly, Category = "LockOn")
	ARMCharacterBase* LockedTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	float LockOnRange = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	float RotationSpeed = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	FName TargetTag = "Enemy";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	TSubclassOf<ARMCharacterBase> TargetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	float RotationThreshold = 30.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	float MinRotationSpeed = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LockOn")
	float MaxRotationSpeed = 10.f;

};
