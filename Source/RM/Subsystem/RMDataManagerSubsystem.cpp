// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RMDataManagerSubsystem.h"
#include "Engine/StreamableManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/AssetManager.h"

void URMDataManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LoadAllDataTables();
}

void URMDataManagerSubsystem::LoadAllDataTables()
{

	TArray<FTableLoadInfo> TablesToLoad = {
		{ TEXT("Skill"), TEXT("/Game/DataTable/DT_SkillData") },
		{ TEXT("Quest"), TEXT("/Game/DataTable/DT_QuestData") }

		// 여기에 더 추가 가능
	};

	for (const FTableLoadInfo& Info : TablesToLoad)
	{
		if (UDataTable* LoadedTable = Cast<UDataTable>(
			StaticLoadObject(UDataTable::StaticClass(), nullptr, *Info.Path)))
		{
			CachedTables.Add(Info.Id, LoadedTable);
		}
	}
}

template<typename T>
const T* URMDataManagerSubsystem::FindRow(FName TableId, FName RowName) const
{
	if (const TObjectPtr<UDataTable>* FoundTable = CachedTables.Find(TableId))
	{
		if (const UDataTable* Table = *FoundTable)
		{
			return Table->FindRow<T>(RowName, TEXT("FindRow"), true);
		}
	}
	return nullptr;
}


