// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RMQuest.generated.h"

class UGameplayAbility;
class ARMCharacterBase;
/**
 * 
 */
UCLASS()
class RM_API URMQuest : public UObject
{
	GENERATED_BODY()
	
public:
    void Initialize(FName InQuestID, ARMCharacterBase* InOwner);

    const bool CouldComplete() const;

    UPROPERTY()
    FName QuestID;

    UPROPERTY()
    FString Description;

    UPROPERTY()
    ARMCharacterBase* QuestOwner;

    UPROPERTY()
    FString MonsterName;

    UPROPERTY()
    int32 TargetCount;

    UPROPERTY()
    int32 CurrentCount = 0;

    bool bIsCompleted = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<TSubclassOf<UGameplayAbility>> SkillRewards;

    void Complete();
    
    void IncreaseKillCount();
	
};
