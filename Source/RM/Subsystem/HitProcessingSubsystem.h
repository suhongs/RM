// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Common/FRMSkillId.h"
#include "DataTable/RMSkillData.h"
#include "GameplayTagContainer.h"
#include "HitProcessingSubsystem.generated.h"

/**
 * 
 */
class ARMCharacterBase;
struct FRMSkillData;
struct FHitResult;

UCLASS()
class RM_API UHitProcessingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	// ÇÙ½É ÇÔ¼ö
	void ProcessHit(ARMCharacterBase* InstigatorActor, const FHitResult& HitResult, const FRMSkillId& SkillId);

	const FRMSkillData* GetSkillDataById(const FRMSkillId& InSkillId);

};
