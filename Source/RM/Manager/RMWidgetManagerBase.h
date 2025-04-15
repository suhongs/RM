// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RMWidgetManagerBase.generated.h"

class ARMCharacterBase;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FRMWidgetManagerParams
{
	GENERATED_BODY()

	FRMWidgetManagerParams() {}
	FRMWidgetManagerParams(
		APlayerController* InPlayerController,
		APlayerState* InPlayerState,
		ARMCharacterBase* InPawn,
		UAbilitySystemComponent* InAbilitySystemComponent
	) : PlayerController(InPlayerController)
		, PlayerState(InPlayerState)
		, Pawn(InPawn)
		, AbilitySystemComponent(InAbilitySystemComponent)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<ARMCharacterBase> Pawn = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAbilitySystemComponent* AbilitySystemComponent = nullptr;
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class RM_API URMWidgetManagerBase : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void InitWidget();

	/** ���� ���� �� ȭ�鿡 ǥ�� */
	virtual void CreateAndAddWidget();

	/** ���� ���� (ȭ�鿡�� ����) */
	virtual void RemoveWidget();

	/** ���� ���̱� */
	virtual void ShowWidget();

	/** ���� ����� */
	virtual void HideWidget();

	/** ���� Visibility ���� */
	virtual void SetWidgetVisibility(ESlateVisibility NewVisibility);

	/** ���� ���� ��ȯ (ĳ���ÿ�) */
	template<typename T>
	T* GetWidget() const
	{
		return Cast<T>(Widget);
	}

	/** ������ ��ȿ���� */
	UFUNCTION(BlueprintCallable)
	bool IsWidgetValid() const;


	UFUNCTION(BlueprintCallable)
	void SetWidgetManagerParams(const FRMWidgetManagerParams& WMParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();

public:

protected:
	/** ���� ���� */
	virtual UUserWidget* CreateWidgetInternal();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller");
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller");
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller");
	TObjectPtr<ARMCharacterBase> Pawn;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller");
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetClass;

	UPROPERTY()
	TObjectPtr<class UUserWidget> Widget;
};
