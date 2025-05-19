// Fill out your copyright notice in the Description page of Project Settings.


#include "Interact/RMInteractComponent.h"
#include "Interface/RMInteractInterface.h"


// Sets default values

URMInteractComponent::URMInteractComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

    InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
    InteractionBox->SetBoxExtent(FVector(150.0f, 150.0f, 100.0f));
    InteractionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    InteractionBox->SetGenerateOverlapEvents(true);
}

void URMInteractComponent::BeginPlay()
{
	Super::BeginPlay();

    if (GetOwner() && GetOwner()->GetRootComponent())
    {
        InteractionBox->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

        InteractionBox->OnComponentBeginOverlap.AddDynamic(this, &URMInteractComponent::OnBoxBeginOverlap);
        InteractionBox->OnComponentEndOverlap.AddDynamic(this, &URMInteractComponent::OnBoxEndOverlap);
    }
}


void URMInteractComponent::Interact()
{
    AActor* ClosestActor = FindClosestInteractableActor();

    if (ClosestActor && ClosestActor->Implements<URMInteractInterface>())
    {
        IRMInteractInterface* InteractableObjActor = Cast<IRMInteractInterface>(ClosestActor);

        if (InteractableObjActor)
        {
            InteractableObjActor->Interact_Implementation(Cast<ACharacter>(GetOwner()));
        }
    }
}

AActor* URMInteractComponent::FindClosestInteractableActor() const
{
    if (OverlappingActors.Num() == 0) return nullptr;

    FVector PlayerLocation = GetOwner()->GetActorLocation();
    AActor* ClosestActor = nullptr;
    float MinDistance = TNumericLimits<float>::Max();

    for (AActor* Actor : OverlappingActors)
    {
        float Distance = FVector::Dist(PlayerLocation, Actor->GetActorLocation());
        if (Distance < MinDistance)
        {
            MinDistance = Distance;
            ClosestActor = Actor;
        }
    }

    return ClosestActor;
}


void URMInteractComponent::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->Implements<URMInteractInterface>())
    {
        IRMInteractInterface* InteractableObject = Cast<IRMInteractInterface>(OtherActor);

        if (InteractableObject)
        {
            InteractableObject->ShowWidget_Implementation(Cast<ACharacter>(GetOwner()));
            OverlappingActors.Add(OtherActor);
        }
    }
}

void URMInteractComponent::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->Implements<URMInteractInterface>())
    {
        IRMInteractInterface* InteractableObject = Cast<IRMInteractInterface>(OtherActor);

        if (InteractableObject)
        {
            InteractableObject->HideWidget_Implementation(Cast<ACharacter>(GetOwner()));
            OverlappingActors.Remove(OtherActor);
        }
    }

    if (OnOverlapEnded.IsBound())
    {
        OnOverlapEnded.Broadcast();
    }
}
