// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "RMDataManagerSubsystem.generated.h"

USTRUCT(BlueprintType)
struct FTableLoadInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data Table")
	FString Path;
};


UCLASS()
class RM_API URMDataManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	template<typename T>
	const T* FindRow(FName TableId, FName RowName) const;

private:
	TMap<FName, TObjectPtr<UDataTable>> CachedTables;

	void LoadAllDataTables();

	//void OnDataTableLoaded(const FTableLoadInfo& TableInfo);
};