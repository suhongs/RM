// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interact/RMInteractableActorBase.h"
#include "RMNonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class RM_API ARMNonPlayerCharacter : public AActor
{
	GENERATED_BODY()
	
public:
	ARMNonPlayerCharacter();

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent;
};
