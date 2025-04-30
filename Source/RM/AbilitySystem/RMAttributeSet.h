// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystem/RMAbilitySystemComponent.h"
#include "RMAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float, float);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnManaChangedDelegate, float, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectExecuted, const FGameplayEffectModCallbackData&)

UCLASS()
class RM_API URMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	URMAttributeSet();

	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
public:

	// ========== Health ==========
	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Health")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, CurrentHealth);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, MaxHealth);

	// ========== Mana ==========
	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Mana")
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, CurrentMana);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Mana")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, MaxMana);

	// ========== Combat ==========
	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Combat")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, AttackPower);

	UPROPERTY(BlueprintReadOnly, Category = "Attribute|Combat")
	FGameplayAttributeData DefencePower;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, DefencePower);

public:
	FOnHealthChangedDelegate OnHealthChanged;
	FOnManaChangedDelegate OnManaChanged;

	FOnEffectExecuted OnEffectExecuted;

};
