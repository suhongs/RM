// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectPool/RMPooledActorBase.h"
#include "RMFloatingDamage.generated.h"


class UWidgetComponent;
class UUserWidget;
UCLASS(Blueprintable)
class RM_API ARMFloatingDamage : public ARMPooledActorBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARMFloatingDamage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	void SetDamageText(float InDamage);
	void StartWidgetAnimation();
	void UpdateWidgetLocation(float DeltaTime);
	void StartFloating(FVector3d StartPosition);

public:
	virtual void InitObject() override;
	virtual void ResetObject() override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> FloatingWidgetClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingDamage", meta = (AllowPrivateAccess = "true"))
	float TotalPlayTime = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FloatingDamage", meta = (AllowPrivateAccess = "true"))
	float FloatingSpeed = 25.f;

	float CurrentPlayTime = 0.f;

};
