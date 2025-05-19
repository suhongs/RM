// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "RMQuestData.generated.h"

class UGameplayAbility;
/**
 * 
 */
USTRUCT(BlueprintType)
struct RM_API FRMQuestData : public FTableRowBase
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FName QuestID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString Description;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    FString MonsterName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    int32 TargetCount=0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    TArray<TSubclassOf<UGameplayAbility>> SkillRewards;
};