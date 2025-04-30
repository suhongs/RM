// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPool/RMObjectPool.h"
#include "RMObjectPool.h"
#include "ObjectPool/RMPooledActorBase.h"

void URMObjectPool::InitializePool(TSubclassOf<ARMPooledActorBase> WidgetClass)
{
	ObjectClass = WidgetClass;
}

ARMPooledActorBase* URMObjectPool::RequestObject(UWorld* World)
{
	if (ObjectPool.Num() > 0)
	{
		ARMPooledActorBase* Object = ObjectPool.Pop(EAllowShrinking::No);
		return Object;
	}
	else if (AllCreatedObjects.Num() < MaxPoolSize)
	{
		ARMPooledActorBase* NewObject = World->SpawnActor<ARMPooledActorBase>(ObjectClass);

		if (NewObject)
		{
			NewObject->InitObject();
			AllCreatedObjects.Add(NewObject);
			return NewObject;
		}
	}

	return nullptr;
}

void URMObjectPool::ReturnObject(ARMPooledActorBase* Object)
{
	if (Object && AllCreatedObjects.Contains(Object))
	{
		if (!ObjectPool.Contains(Object))
		{
			ObjectPool.Add(Object);
		}
	}
}

void URMObjectPool::FreeAllObjects()
{
	ObjectPool.Reset();
	AllCreatedObjects.Reset();
}
