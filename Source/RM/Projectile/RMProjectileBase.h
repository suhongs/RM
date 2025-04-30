// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Common/FRMSkillId.h"
#include "RMProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class ARMCharacterBase;


UCLASS()
class RM_API ARMProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARMProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void InitProjectile(ARMCharacterBase* InOnwer);
    void InitVelocity(FVector Direction);

    UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult);

private:
    UPROPERTY()
    TObjectPtr<ARMCharacterBase> OwnerCharacter;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SkillId", meta = (AllowPrivateAccess = "true"))
    FRMSkillId SkillId = 0;

    // 투사체의 이동을 관리하는 컴포넌트
    UPROPERTY(VisibleAnywhere, Category = "Movement")
    UProjectileMovementComponent* ProjectileMovementComponent;

    // 투사체의 메쉬 (선택적)
    UPROPERTY(VisibleAnywhere, Category = "Mesh")
    UStaticMeshComponent* ProjectileMesh;

    // 투사체의 스피드 (속도)
    UPROPERTY(EditAnywhere, Category = "Projectile")
    float Speed = 3000.0f;  // 예시로 3000으로 설정

private:
    UPROPERTY(VisibleAnywhere, Category = "Collision")
    USphereComponent* CollisionComponent;
	
};
