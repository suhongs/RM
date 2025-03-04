// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RMCharacterBase.h"


// Sets default values
ARMCharacterBase::ARMCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARMCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARMCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARMCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

