// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Common/FRMSkillId.h"
#include "GameplayTagContainer.h"
#include "RMSkillData.generated.h"

class URMGameplayEffectBase;

USTRUCT(BlueprintType)
struct FRMSkillData : public FTableRowBase
{
	GENERATED_BODY()

public:
	// Skill ID (RowName�� ��ġ�ؾ� ��)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRMSkillId SkillId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag SkillTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<URMGameplayEffectBase> Effects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Cooldown = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UAnimMontage> Montage;

	// ��� �ʿ��� �ʵ� �߰� ���� (��: ��Ÿ�, �ߵ� �ð�, ȿ�� ��)
};