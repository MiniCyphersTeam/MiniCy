// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersProjectile.h"
#include "ShivaNormalAttackProjectile.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AShivaNormalAttackProjectile : public AMiniCyphersProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShivaNormalAttackProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile) //��ü �ݸ��� ������Ʈ
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, Category = Movement) //������Ÿ�� �����Ʈ ������Ʈ
		class UProjectileMovementComponent* ProjectileMovementComp;

	AController* SetCharacterController(AController* Controller);
	AController* CharacterController;

};
