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

	/** 위젯 생성 및 화면에 표시 */
	virtual void CreateAndAddWidget();

	/** 위젯 제거 (화면에서 제거) */
	virtual void RemoveWidget();

	/** 위젯 보이기 */
	virtual void ShowWidget();

	/** 위젯 숨기기 */
	virtual void HideWidget();

	/** 위젯 Visibility 설정 */
	virtual void SetWidgetVisibility(ESlateVisibility NewVisibility);

	/** 현재 위젯 반환 (캐스팅용) */
	template<typename T>
	T* GetWidget() const
	{
		return Cast<T>(Widget);
	}

	/** 위젯이 유효한지 */
	UFUNCTION(BlueprintCallable)
	bool IsWidgetValid() const;


	UFUNCTION(BlueprintCallable)
	void SetWidgetManagerParams(const FRMWidgetManagerParams& WMParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadcastInitialValues();

	virtual void BindCallbacksToDependencies();

public:

protected:
	/** 위젯 생성 */
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
