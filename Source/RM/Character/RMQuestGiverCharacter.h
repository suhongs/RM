// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/RMNonPlayerCharacter.h"
#include "Interface/RMInteractInterface.h"
#include "RMQuestGiverCharacter.generated.h"

class URMQuestGiverComponent;
class UWidgetComponent;
class ARMPlayerCharacter;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnQuestGiverInteracted,
	ARMQuestGiverCharacter*, QuestGiverCharacter, 
	const FString&, DialogueText, 
	bool, bInShowAcceptDecline,
	bool, bInIsComplete);

UCLASS()
class RM_API ARMQuestGiverCharacter : public ARMNonPlayerCharacter, public IRMInteractInterface
{
	GENERATED_BODY()
	
	
public:
	ARMQuestGiverCharacter();

protected:
	virtual void BeginPlay() override;

public:
	URMQuestGiverComponent* GetQuestGiverComponent() const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestGiver", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<URMQuestGiverComponent> QuestGiverComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "QuestGiver", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> InteractWidgetComponent;

public:
	void CreateQuest(ARMPlayerCharacter* PlayerCharacter);

	void CompleteQuest(ARMPlayerCharacter* PlayerCharacter);

public:
	FOnQuestGiverInteracted OnInteracted;

public:
	virtual void Interact_Implementation(ACharacter* InteractingCharacter) override;
	virtual void ShowWidget_Implementation(ACharacter* InteractingCharacter) override;
	virtual void HideWidget_Implementation(ACharacter* InteractingCharacter) override;
	
};
