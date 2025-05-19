// Fill out your copyright notice in the Description page of Project Settings.


#include "Quest/RMQuestGiverComponent.h"
#include "Character/RMCharacterBase.h"
#include "HUD/Widget/RMDialogueWidget.h"
#include "Subsystem/RMQuestSubsystem.h"
#include "HUD/RMHUD.h"
#include "Quest/RMQuest.h"


// Sets default values for this component's properties
URMQuestGiverComponent::URMQuestGiverComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	CurrentQuestIndex = 0;
}


// Called when the game starts
void URMQuestGiverComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


URMQuestSubsystem* URMQuestGiverComponent::GetQuestSubsystem() const
{
	UWorld* World = GetWorld();
	if (!IsValid(World))
		return nullptr;

	UGameInstance* GameInstance = World->GetGameInstance();
	if (!IsValid(GameInstance))
		return nullptr;

	return GameInstance->GetSubsystem<URMQuestSubsystem>();
}

void URMQuestGiverComponent::CreateQuest(ARMCharacterBase* InteractingCharacter) const
{
	if (!QuestIDs.IsValidIndex(CurrentQuestIndex))
		return;

	FName CurrentQuestID = QuestIDs[CurrentQuestIndex];

	URMQuestSubsystem* QuestSubsystem = GetQuestSubsystem();
	if (!IsValid(QuestSubsystem))
		return;

	QuestSubsystem->CreateQuest(InteractingCharacter, CurrentQuestID);
}

void URMQuestGiverComponent::CompleteQuest(ARMCharacterBase* InteractingCharacter)
{
	URMQuestSubsystem* QuestSubsystem = GetQuestSubsystem();
	if (!IsValid(QuestSubsystem))
		return;

	if (QuestIDs.IsValidIndex(CurrentQuestIndex) && QuestSubsystem->IsQuestActived(QuestIDs[CurrentQuestIndex]))
	{
		QuestSubsystem->CompleteQuest(QuestIDs[CurrentQuestIndex]);
		++CurrentQuestIndex;
	}
}

URMQuest* URMQuestGiverComponent::GetCurrentQuest() const
{
	UWorld* World = GetWorld();
	UGameInstance* GameInstance = World ? World->GetGameInstance() : nullptr;
	URMQuestSubsystem* QuestSubsystem = GameInstance ? GameInstance->GetSubsystem<URMQuestSubsystem>() : nullptr;
	if (!IsValid(QuestSubsystem))
		return nullptr;

	if (!QuestIDs.IsValidIndex(CurrentQuestIndex))
		return nullptr;

	FName CurrentQuestID = QuestIDs[CurrentQuestIndex];

	return QuestSubsystem->GetActivedQuestByID(CurrentQuestID);
}

