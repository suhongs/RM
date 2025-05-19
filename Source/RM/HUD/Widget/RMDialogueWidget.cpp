// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/Widget/RMDialogueWidget.h"
#include "HUD/Widget/RMButtonDescriptionWidget.h"
#include "Components/TextBlock.h"
#include "RMDialogueWidget.h"


bool URMDialogueWidget::Initialize()
{
    if (!Super::Initialize()) return false;


    return true;
}

void URMDialogueWidget::OnAcceptQuest()
{
    
    if (OnDialogueEnded.IsBound())
    {
        OnDialogueEnded.Broadcast();
    }
}

void URMDialogueWidget::OnDeclineQuest()
{
    if (OnDialogueEnded.IsBound())
    {
        OnDialogueEnded.Broadcast();
    }
}

void URMDialogueWidget::OnCompleteQuest()
{
    if (OnDialogueEnded.IsBound())
    {
        OnDialogueEnded.Broadcast();
    }
}

void URMDialogueWidget::UpdateDialogue(const FString& DialogueText, bool bShowAcceptDecline)
{
    if (TXT_Dialogue)
    {
        TXT_Dialogue->SetText(FText::FromString(DialogueText));
    }

    if (bShowAcceptDecline)
    {

        if (Accept_Widget) 
            Accept_Widget->SetVisibility(ESlateVisibility::Visible);
        if (Decline_Widget) 
            Decline_Widget->SetVisibility(ESlateVisibility::Visible);

        if (Complete_Widget) 
            Complete_Widget->SetVisibility(ESlateVisibility::Collapsed);
    }
    else
    {
        if (Accept_Widget) 
            Accept_Widget->SetVisibility(ESlateVisibility::Collapsed);
        if (Decline_Widget) 
            Decline_Widget->SetVisibility(ESlateVisibility::Collapsed);

        if (Complete_Widget) 
            Complete_Widget->SetVisibility(ESlateVisibility::Visible);
    }
}

