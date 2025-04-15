// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interface/RMCombatInterface.h"
#include "RMCharacterBase.generated.h"

class URMAbilitySystemComponent;
class URMAttributeSet;
class UGameplayAbility;
class UGameplayEffect;

UCLASS()
class RM_API ARMCharacterBase : public ACharacter, public IAbilitySystemInterface, public IRMCombatInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARMCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void InitAbilityActorInfo();
	virtual void InitDefaultAbility();
	virtual void InitDefaultAttributes();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// AbilitySystem Component
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<URMAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayAbility, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	TSubclassOf<UGameplayEffect> DefaultStatEffect;


public:

	virtual void HitDetection(const FRMSkillId& InSkillId) override;

	virtual void HitReact() override;

	virtual void ClearHitActors() override;
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> WeaponMesh;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> HitActors;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	URMAttributeSet* GetAttributeSet() const { return AttributeSet; }

	
};
