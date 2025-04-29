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

//void URMDataManagerSubsystem::LoadAllDataTables()
//{
//    TArray<FTableLoadInfo> TablesToLoad = {
//        { TEXT("Skill"), TEXT("/Game/DataTable/DT_SkillData") },
//        // 여기에 더 추가 가능
//    };
//
//    // 비동기 로딩
//    for (const FTableLoadInfo& Info : TablesToLoad)
//    {
//        FStreamableManager& AssetLoader = UGameplayStatics::GetStreamableManager();
//        TAssetPtr<UDataTable> TablePtr = FAssetPtr<UDataTable>(FSoftObjectPath(Info.Path));
//
//        // 비동기 로딩, 로딩 후에 OnDataTableLoaded 호출
//        AssetLoader.RequestAsyncLoad(TablePtr.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &URMDataManagerSubsystem::OnDataTableLoaded, Info));
//    }
//}
//
//void URMDataManagerSubsystem::OnDataTableLoaded(const FTableLoadInfo& TableInfo)
//{
//    if (UDataTable* LoadedTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *TableInfo.Path)))
//    {
//        CachedTables.Add(TableInfo.Id, LoadedTable);
//    }
//}
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


