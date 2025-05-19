// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/RMInteractableActorBase.h"


// Sets default values
ARMInteractableActorBase::ARMInteractableActorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ARMInteractableActorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARMInteractableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

