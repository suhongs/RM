// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMNonPlayerCharacter.h"

ARMNonPlayerCharacter::ARMNonPlayerCharacter()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	RootComponent = SkeletalMeshComponent;
}

void ARMNonPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}
