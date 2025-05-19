// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMDialogueWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDialogueEnded);

class UButton;
class UTextBlock;
class URMButtonDescriptionWidget;


UCLASS()
class RM_API URMDialogueWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;
	
public:
    UFUNCTION(BlueprintCallable, Category = "Quest")
    void OnAcceptQuest();

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void OnDeclineQuest();

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void OnCompleteQuest();

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void UpdateDialogue(const FString& DialogueText, bool bShowAcceptDecline);

    FOnDialogueEnded OnDialogueEnded;

protected:

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<URMButtonDescriptionWidget> Accept_Widget;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<URMButtonDescriptionWidget> Decline_Widget;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<URMButtonDescriptionWidget> Complete_Widget;

    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    TObjectPtr<UTextBlock> TXT_Dialogue;
	
	
};
