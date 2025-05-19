// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RMInteractInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URMInteractInterface : public UInterface
{
	GENERATED_BODY()
};


class RM_API IRMInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void Interact(ACharacter* InteractingCharacter);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void ShowWidget(ACharacter* InteractingCharacter);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void HideWidget(ACharacter* InteractingCharacter);

};
