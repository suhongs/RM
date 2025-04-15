// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RMCharacterBase.h"
#include "RMPlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

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
	UFUNCTION(BlueprintCallable)
	virtual void HitDetection(const FRMSkillId& InSkillId) override;
	UFUNCTION(BlueprintCallable)
	virtual void HitReact() override;

	
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Effects/LightAttack")
	TSubclassOf<UGameplayEffect> LightAttackEffect;

public:
	UFUNCTION(BlueprintCallable)
	void RotateCharacterToCameraYaw();
};
