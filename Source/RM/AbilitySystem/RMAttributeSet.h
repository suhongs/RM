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

/**
 * 
 */
UCLASS()
class RM_API URMAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	URMAttributeSet();

	/** 체력 */
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, Health);

	/** 스태미나 */
	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(URMAttributeSet, Stamina);
	
};
