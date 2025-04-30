// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RMObjectPool.generated.h"

/**
 * 
 */
class ARMPooledActorBase;
class IRMObjectPoolableInterface;

UCLASS(Blueprintable)
class RM_API URMObjectPool : public UObject
{
	GENERATED_BODY()
	
public:
	void InitializePool(TSubclassOf<ARMPooledActorBase> WidgetClass);

public:
	ARMPooledActorBase* RequestObject(UWorld* World);
	void ReturnObject(ARMPooledActorBase* Object);
	void FreeAllObjects();


private:
	UPROPERTY()
	TArray<TObjectPtr<ARMPooledActorBase>> ObjectPool;

	UPROPERTY()
	TArray<TObjectPtr<ARMPooledActorBase>> AllCreatedObjects;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ARMPooledActorBase> ObjectClass;

	int32 MaxPoolSize = 20;

};
