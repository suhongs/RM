
// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RMDialogueSubsystem.h"
#include "Character/RMQuestGiverCharacter.h"
#include "Character/RMPlayerCharacter.h"
#include "Player/RMPlayerController.h"
#include "Interact/RMInteractComponent.h"
#include "HUD/Widget/RMDialogueWidget.h"
#include "Quest/RMQuestGiverComponent.h"

URMDialogueSubsystem::URMDialogueSubsystem()
{
	static ConstructorHelpers::FClassFinder<URMDialogueWidget> DialogueWBPClass(TEXT("/Game/UI/Dialogue/WBP_Dialogue"));

	if (DialogueWBPClass.Succeeded())
	{
		DialogueWidgetClass = DialogueWBPClass.Class;
	}
}

void URMDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void URMDialogueSubsystem::RegistPlayerCharacter(ARMPlayerCharacter* InPlayerCharacter)
{
	PlayerCharacter = InPlayerCharacter;

	if (!IsValid(PlayerCharacter))
		return;

	PC = PlayerCharacter->GetController<ARMPlayerController>();

	URMInteractComponent* InteractComponent = PlayerCharacter->GetInteractComponent();
	if (!IsValid(InteractComponent))
		return;

	if (InteractComponent->InteractionBox == nullptr)
		return;

	InteractComponent->OnOverlapEnded.AddDynamic(this, &URMDialogueSubsystem::RemoveDialogueWidget);
}

void URMDialogueSubsystem::RegistInteractableActor(AActor* InActor)
{
	if (!IsValid(InActor))
		return;

	ARMQuestGiverCharacter* Character = Cast<ARMQuestGiverCharacter>(InActor);
	if (!IsValid(Character))
		return;

	Character->OnInteracted.AddDynamic(this, &URMDialogueSubsystem::DisplayDialogueWidget);
}

void URMDialogueSubsystem::DisplayDialogueWidget(ARMQuestGiverCharacter* QuestGiverCharacter, const FString& DialogueText, bool bInShowAcceptDecline, bool bInIsQuestComplete)
{
	if (IsValid(CurrentDisplayedWidget))
		return;

	InteractionTarget = QuestGiverCharacter;

	if (DialogueWidgetClass != nullptr && PC != nullptr)
	{
		CurrentDisplayedWidget = CreateDialogueWidget();

		if (IsValid(CurrentDisplayedWidget))
		{
			PC->bIsDialogueMode = true;
			bShowAcceptDecline = bInShowAcceptDecline;
			bIsQuestComplete = bInIsQuestComplete;
			CurrentDisplayedWidget->UpdateDialogue(DialogueText, bInShowAcceptDecline);
			CurrentDisplayedWidget->AddToViewport();
		}
	}
}

void URMDialogueSubsystem::RemoveDialogueWidget()
{
	if (IsValid(CurrentDisplayedWidget) && CurrentDisplayedWidget->IsInViewport())
	{
		PC->bIsDialogueMode = false;
		CurrentDisplayedWidget->RemoveFromParent();
		CurrentDisplayedWidget = nullptr;
	}
}

URMDialogueWidget* URMDialogueSubsystem::CreateDialogueWidget()
{
	if (DialogueWidgetClass != nullptr && PC != nullptr)
		return CreateWidget<URMDialogueWidget>(PC, DialogueWidgetClass);

	return nullptr;
}

void URMDialogueSubsystem::HandleDialogueClick(bool bIsLeftClick)
{
	if (!IsValid(InteractionTarget))
		return;

	if (!IsValid(PlayerCharacter))
		return;
	URMQuestGiverComponent* QuestGiverComponent = InteractionTarget->GetQuestGiverComponent();
	if (!IsValid(QuestGiverComponent))
		return;


	if (bShowAcceptDecline)
	{
		if (bIsLeftClick)
		{
			QuestGiverComponent->CreateQuest(PlayerCharacter);
		}
	}
	else
	{
		if (bIsQuestComplete)
		{
			QuestGiverComponent->CompleteQuest(PlayerCharacter);
		}
	}

	RemoveDialogueWidget();
}
