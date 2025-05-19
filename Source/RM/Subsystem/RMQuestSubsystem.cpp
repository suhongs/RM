// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RMQuestSubsystem.h"
#include "Subsystem/RMDataManagerSubsystem.h"
#include "Quest/RMQuest.h"

void URMQuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    UE_LOG(LogTemp, Log, TEXT("Quest Subsystem Initialized!"));
}

void URMQuestSubsystem::CreateQuest(ARMCharacterBase* QuestOwner, const FName QuestID)
{
    UWorld* World = GetWorld();
    if (!IsValid(World))
        return;

    UGameInstance* GameInstance = World->GetGameInstance();
    if (!IsValid(GameInstance))
        return;

    URMDataManagerSubsystem* DataManager = GameInstance->GetSubsystem<URMDataManagerSubsystem>();
    if (!IsValid(DataManager))
        return;

    const FRMQuestData* QuestData = DataManager->FindRow<FRMQuestData>(FName("Quest"), QuestID);
    if (!QuestData)
        return;

    URMQuest* NewQuest = NewObject<URMQuest>(this);
    NewQuest->QuestID = QuestID;
    NewQuest->QuestOwner = QuestOwner;
    NewQuest->MonsterName = QuestData->MonsterName;
    NewQuest->TargetCount = QuestData->TargetCount;
    NewQuest->CurrentCount = 0;
    NewQuest->SkillRewards = QuestData->SkillRewards;
    ActiveQuests.Add(QuestID, NewQuest);
}

URMQuest* URMQuestSubsystem::GetActivedQuestByID(const FName QuestID)
{
    return ActiveQuests.FindRef(QuestID);
}


void URMQuestSubsystem::CompleteQuest(FName QuestID)
{
    if (URMQuest* Quest = ActiveQuests.FindRef(QuestID))
    {
        Quest->Complete();
        ActiveQuests.Remove(QuestID);

        UE_LOG(LogTemp, Log, TEXT("Quest Completed: %s"), *QuestID.ToString());

        UE_LOG(LogTemp, Log, TEXT("NPC에게 돌아가 다음 퀘스트를 받아야 합니다."));
    }
}

void URMQuestSubsystem::OnMonsterKilled(const FName MonsterName)
{
    for (auto& QuestPair : ActiveQuests)
    {
        URMQuest* Quest = QuestPair.Value;
        if (!IsValid(Quest))
            continue;

        if (Quest->MonsterName == MonsterName)
        {
            Quest->IncreaseKillCount();
        }
    }
}

bool URMQuestSubsystem::IsQuestActived(FName QuestID) const
{
    return ActiveQuests.Contains(QuestID);
}



void URMQuestSubsystem::LoadQuests()
{
    // 추후 SaveGame에서 로드하는 코드 작성
}

void URMQuestSubsystem::SaveQuests()
{
    // 추후 SaveGame에 저장하는 코드 작성
}


