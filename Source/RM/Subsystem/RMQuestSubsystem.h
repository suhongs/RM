// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DataTable/RMQuestData.h"
#include "RMQuestSubsystem.generated.h"

class URMQuest;
class ARMCharacterBase;
/**
 * 
 */
UCLASS()
class RM_API URMQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    void CreateQuest(ARMCharacterBase* QuestOwner, const FName QuestID);
    URMQuest* GetActivedQuestByID(const FName QuestID);
    bool IsQuestActived(FName QuestID) const;
    void CompleteQuest(FName QuestID);

    void OnMonsterKilled(const FName MonsterName);

    UPROPERTY()
    TMap<FName, URMQuest*> ActiveQuests;

    void LoadQuests();
    void SaveQuests();
	
};
