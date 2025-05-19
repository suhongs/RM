// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RMCharacterBase.h"
#include "Interface/RMCombatInterface.h"
#include "Interface/RMLockOnTargetInterface.h"
#include "RMEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RM_API ARMEnemyCharacter : public ARMCharacterBase , public IRMLockOnTargetInterface
{
	GENERATED_BODY()
	
public:
	ARMEnemyCharacter();

	virtual void PossessedBy(AController* NewController) override;

	//UFUNCTION(BlueprintCallable)
	//virtual void HighlightActor();

	//UFUNCTION(BlueprintCallable)
	//virtual void UnHighlightActor();

public:
	UFUNCTION(BlueprintCallable)
	virtual void HitDetection(const FRMSkillId& InSkillId) override;
	UFUNCTION(BlueprintCallable)
	virtual void HitReact() override;


protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

public:
	virtual void CharacterDead() override;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<class URMFloatingHpBarWidgetComponent> FloatingHealthBarWidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widget")
	TObjectPtr<class URMInbodyCursorWidgetComponent> InbodyCursorWidgetComponent;
public:
	virtual void ShowInbodyCursor() override;
	virtual void HideInbodyCursor() override;


	
};
