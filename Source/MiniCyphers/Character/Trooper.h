// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NonPlayableCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Trooper.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API ATrooper : public ANonPlayableCharacter
{
	GENERATED_BODY()

public:
	ATrooper();

public:
	virtual void BeginPlay() override;
	virtual void OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee) override;
};
