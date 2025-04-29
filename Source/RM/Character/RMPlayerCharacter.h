// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RMCharacterBase.h"
#include "RMPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class URMAimComponent;

/**
 * 
 */
UCLASS()
class RM_API ARMPlayerCharacter : public ARMCharacterBase
{
	GENERATED_BODY()
	
public:
	ARMPlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void InitAbilityActorInfo();

public:
	URMAimComponent* GetAimComponent() const { return AimComponent; }

	UFUNCTION(BlueprintCallable)
	void RotateCharacterToCameraYaw();

public:
	UFUNCTION(BlueprintCallable)
	virtual void HitDetection(const FRMSkillId& InSkillId) override;
	UFUNCTION(BlueprintCallable)
	virtual void HitReact() override;
	UFUNCTION(BlueprintCallable)
	void ThrowSpear();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpearMesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMesh* SpearMesh;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpearMesh", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ARMProjectileBase> ProjectileClass;

private:
	UPROPERTY(VisibleAnywhere, Category = "Aim")
	TObjectPtr<URMAimComponent> AimComponent;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects/LightAttack")
	TSubclassOf<UGameplayEffect> LightAttackEffect;

};
