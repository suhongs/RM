// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FRMSkillId.generated.h"

USTRUCT(BlueprintType)
struct FRMSkillId
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SkillId = 0;

	static const uint32 Invalid = 0;

	FRMSkillId() : SkillId(Invalid) {}
	FRMSkillId(uint32 InValue) : SkillId(InValue) {}

	bool IsValid() const { return SkillId != Invalid; }

	FORCEINLINE bool operator==(const FRMSkillId& Other) const { return SkillId == Other.SkillId; }
	FORCEINLINE bool operator!=(const FRMSkillId& Other) const { return SkillId != Other.SkillId; }
	FORCEINLINE bool operator<(const FRMSkillId& Other) const { return SkillId < Other.SkillId; }

	FORCEINLINE FString ToString() const
	{
		return FString::Printf(TEXT("SkillId: %u"), SkillId);
	}

	FORCEINLINE FName ToRowName() const
	{
		return FName(*FString::FromInt(SkillId));
	}

	friend FORCEINLINE uint32 GetTypeHash(const FRMSkillId& InSkillId)
	{
		return ::GetTypeHash(InSkillId.SkillId);
	}

};