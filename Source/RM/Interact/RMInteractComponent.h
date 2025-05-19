// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "RMInteractComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverlapEnded);

class ARMCharacterBase;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RM_API URMInteractComponent : public UActorComponent 
{
	GENERATED_BODY()

public:
    URMInteractComponent();
    virtual void BeginPlay() override;

    void Interact();

    AActor* FindClosestInteractableActor() const;

public:
    UPROPERTY(VisibleAnywhere, Category = "Interaction")
    UBoxComponent* InteractionBox;

    FOnOverlapEnded OnOverlapEnded;
protected:
    UPROPERTY()
    TArray<AActor*> OverlappingActors;

    UFUNCTION()
    void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

    UFUNCTION()
    void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
