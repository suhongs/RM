// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RMHUD.generated.h"

class UAbilitySystemComponent;
class ARMCharacterBase;
class URMWidgetManagerBase;
class URMHUDWidgetManager;

/**
 * 
 */
UCLASS()
class RM_API ARMHUD : public AHUD
{
	GENERATED_BODY()
	
	
public:
	virtual void BeginPlay() override;
	void InitHUD(APlayerController* InPC, APlayerState* InPS, ARMCharacterBase* InActor, UAbilitySystemComponent* InAbilitySystemComponent);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Widget")
	TSubclassOf<URMWidgetManagerBase> HUDWidgetManagerClass;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URMHUDWidgetManager> HUDWidgetManager;
	
	/*�κ��丮 ���� �� InventoryWidgetManager ����
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<URMInventoryWidgetManager> InventoryWidgetManager;
	*/
};
