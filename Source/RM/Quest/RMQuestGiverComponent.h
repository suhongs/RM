// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RMQuestGiverComponent.generated.h"

class URMDialogueWidget;
class ACharacter;
class URMQuest;
class ARMCharacterBase;
class URMQuestSubsystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RM_API URMQuestGiverComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URMQuestGiverComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Quest")
	TArray<FName> QuestIDs;

	UPROPERTY(EditAnywhere, Category = "Quest")
	uint32 CurrentQuestIndex = 0;

private:
	URMQuestSubsystem* GetQuestSubsystem() const;

public:
	
	void CreateQuest(ARMCharacterBase* InteractingCharacter) const;
	void CompleteQuest(ARMCharacterBase* InteractingCharacter);

	URMQuest* GetCurrentQuest() const;
};
