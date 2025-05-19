// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/RMProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Interface/RMCombatInterface.h"
#include "Subsystem/HitProcessingSubsystem.h"

// Sets default values
ARMProjectileBase::ARMProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 3000.f;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bShouldBounce = false;  // ƨ�� ����
	ProjectileMovementComponent->ProjectileGravityScale = 0.2f;  // �߷� ���� ���ֱ�
	ProjectileMovementComponent->bRotationFollowsVelocity = true;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(10.f);
	CollisionComponent->SetGenerateOverlapEvents(true);


}

// Called when the game starts or when spawned
void ARMProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
	if (CollisionComponent)
	{
		CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ARMProjectileBase::OnOverlapBegin);
	}
}

// Called every frame
void ARMProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARMProjectileBase::InitProjectile(ARMCharacterBase* InOnwer)
{
	OwnerCharacter = InOnwer;
}

void ARMProjectileBase::InitVelocity(FVector Direction)
{
	if (IsValid(ProjectileMovementComponent))
	{
		// ������ �������� �ӵ� �ʱ�ȭ
		ProjectileMovementComponent->Velocity = Direction * Speed;
	}
}

void ARMProjectileBase::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Log, TEXT("Projectile overlapped: %s"), *OtherActor->GetName());

		// ������ ó��, ����Ʈ ���, �ı� ��
		UHitProcessingSubsystem* HitProcessingSubsystem = GetGameInstance()->GetSubsystem<UHitProcessingSubsystem>();
		if (HitProcessingSubsystem == nullptr)
			return;

		ARMCharacterBase* HitCharacter = Cast<ARMCharacterBase>(OtherActor);

		IRMCombatInterface* CombatInterface = Cast<IRMCombatInterface>(HitCharacter);

		if (HitCharacter && CombatInterface)
		{
			HitProcessingSubsystem->ProcessHit(OwnerCharacter, SweepResult, SkillId);

			CombatInterface->HitReact();
		}

		Destroy();
	}
}

