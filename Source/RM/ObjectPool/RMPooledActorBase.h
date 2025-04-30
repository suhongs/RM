// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/RMObjectPoolableInterface.h"
#include "RMPooledActorBase.generated.h"

UCLASS()
class RM_API ARMPooledActorBase : public AActor, public IRMObjectPoolableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARMPooledActorBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void InitObject() override;
	virtual void ResetObject() override;
	
};
