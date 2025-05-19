// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RMButtonDescriptionWidget.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RM_API URMButtonDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UImage> IMG_Button;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UTextBlock> TXT_Description;
};
