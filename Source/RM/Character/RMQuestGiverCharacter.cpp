// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMQuestGiverCharacter.h"
#include "Quest/RMQuestGiverComponent.h"
#include "Components/WidgetComponent.h"
#include "Character/RMPlayerCharacter.h"
#include "Quest/RMQuest.h"
#include "Subsystem/RMDialogueSubsystem.h"

ARMQuestGiverCharacter::ARMQuestGiverCharacter()
{
	QuestGiverComponent = CreateDefaultSubobject<URMQuestGiverComponent>(TEXT("QuestGiverComponent"));

    InteractWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComponent"));
    InteractWidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
    InteractWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    InteractWidgetComponent->SetDrawSize(FVector2D(150.f, 50.f));
    InteractWidgetComponent->SetVisibility(false);  // �⺻������ ����
}

void ARMQuestGiverCharacter::BeginPlay()
{
	Super::BeginPlay();


    if (InteractWidgetComponent->GetWidget() == nullptr)
    {
        UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), InteractWidgetComponent->GetWidgetClass());
        InteractWidgetComponent->SetWidget(Widget);
    }

    URMDialogueSubsystem* DialogueSubsystem = GetGameInstance()->GetSubsystem<URMDialogueSubsystem>();
    if (IsValid(DialogueSubsystem))
    {
        DialogueSubsystem->RegistInteractableActor(this);
    }

}

URMQuestGiverComponent* ARMQuestGiverCharacter::GetQuestGiverComponent() const
{
    return QuestGiverComponent;
}

void ARMQuestGiverCharacter::CreateQuest(ARMPlayerCharacter* PlayerCharacter)
{
    if (IsValid(QuestGiverComponent))
    {
        QuestGiverComponent->CreateQuest(PlayerCharacter);
    }
}

void ARMQuestGiverCharacter::CompleteQuest(ARMPlayerCharacter* PlayerCharacter)
{
    QuestGiverComponent->CompleteQuest(PlayerCharacter);
}

void ARMQuestGiverCharacter::Interact_Implementation(ACharacter* InteractingCharacter)
{
    if (!IsValid(InteractingCharacter))
        return;

    if (!IsValid(QuestGiverComponent))
        return;

    UE_LOG(LogTemp, Log, TEXT("%s interact with %s"), *InteractingCharacter->GetName(),*GetName());

    URMQuest* CurrentQuest = QuestGiverComponent->GetCurrentQuest();

    if (CurrentQuest == nullptr)
    {
        if (OnInteracted.IsBound())
        {
            OnInteracted.Broadcast(this, TEXT("Are you ready to start the quest ? "), true, false);
        }
    }
    else
    {
        if (!CurrentQuest->CouldComplete())
        {
            // ����Ʈ�� ���������� ������ �Ϸ���� ���� ����
            FString QuestInfo = FString::Printf(TEXT("%s: %d / %d"), *CurrentQuest->MonsterName, CurrentQuest->CurrentCount, CurrentQuest->TargetCount);
            OnInteracted.Broadcast(this, QuestInfo, false, false);
        }
        else
        {
            // ����Ʈ �Ϸ� ������ ����
            OnInteracted.Broadcast(this, TEXT("Quest Complete!"), false, true);
        }
    }
}

void ARMQuestGiverCharacter::ShowWidget_Implementation(ACharacter* InteractingCharacter)
{
    if (InteractWidgetComponent && !InteractWidgetComponent->IsVisible())
    {
        UE_LOG(LogTemp, Log, TEXT("Show %s Interact Widget."), *GetName());
        InteractWidgetComponent->SetVisibility(true);
    }
}

void ARMQuestGiverCharacter::HideWidget_Implementation(ACharacter* InteractingCharacter)
{
    if (InteractWidgetComponent && InteractWidgetComponent->IsVisible())
    {
        UE_LOG(LogTemp, Log, TEXT("Hide %s Interact Widget."), *GetName());
        InteractWidgetComponent->SetVisibility(false);
    }
}
