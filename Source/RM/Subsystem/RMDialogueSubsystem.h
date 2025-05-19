// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "RMDialogueSubsystem.generated.h"

/**
 * 
 */

class URMDialogueWidget;
class ARMPlayerCharacter;
class ARMPlayerController;
class ARMQuestGiverCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDialogueClick, bool, bIsLeftClick);

UCLASS()
class RM_API URMDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
	
public:
	URMDialogueSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

public:
	void RegistPlayerCharacter(ARMPlayerCharacter* InPlayerCharacter);

	void RegistInteractableActor(AActor* InActor);

	UFUNCTION()
	void DisplayDialogueWidget(ARMQuestGiverCharacter* QuestGiverCharacter, const FString& DialogueText, bool bInShowAcceptDecline, bool bInIsQuestComplete);

	UFUNCTION()
	void RemoveDialogueWidget();

	void HandleDialogueClick(bool bIsLeftClick);
private:
	URMDialogueWidget* CreateDialogueWidget();

public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<URMDialogueWidget> DialogueWidgetClass;

	//WidgetPool
	UPROPERTY()
	TObjectPtr<URMDialogueWidget> CurrentDisplayedWidget;;

	UPROPERTY()
	TObjectPtr<ARMPlayerController> PC;

	UPROPERTY()
	TObjectPtr<ARMPlayerCharacter> PlayerCharacter;

	UPROPERTY()
	TObjectPtr<ARMQuestGiverCharacter> InteractionTarget;

	UPROPERTY()
	bool bShowAcceptDecline;

	UPROPERTY()
	bool bIsQuestComplete;

	FOnDialogueClick OnDialogueClick;
	
};
