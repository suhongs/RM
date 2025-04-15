// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/DataTable.h"
#include "RMDataManagerSubsystem.generated.h"

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
};