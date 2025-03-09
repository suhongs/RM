// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "RMCharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayAbility;

UCLASS()
class RM_API ARMCharacterBase : public ACharacter, public IAbilitySystemInterface
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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

public:
	// AbilitySystem Component
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayAbility, meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<UGameplayAbility>> DefaultAbilities;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	
};
