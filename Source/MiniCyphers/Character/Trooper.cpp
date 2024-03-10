// Fill out your copyright notice in the Description page of Project Settings.


#include "Trooper.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"
#include "../AI/MiniCyphersAIController.h"

ATrooper::ATrooper()
{
	// AIControllerClass = BP�� �� ��Ƽ�� AI Controller�� �־��� ��
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ATrooper::BeginPlay()
{
	bSuperArmor = true; // �����۴� �׽� ���۾Ƹ�
	IsPlayerTeam = false; // �� ��
}

AMiniCyphersCharacter* ATrooper::GetTarget()
{
	if (LastAttacker != nullptr)
		return LastAttacker;

	// Ÿ���� �̵�
	return Super::GetTarget();
}

void ATrooper::OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee)
{
	Super::OnHit(Attacker, DamageType, StiffTime, HealthAmount, UpperVelocity, KnockBackDistance, isMelee);
	
	LastAttacker = Attacker;
	LastAttackDeltaTime = 0.0f;
}

void ATrooper::Tick(float DeltaTime)
{
	if (LastAttackTrackingValidTime < LastAttackDeltaTime)
	{
		LastAttacker = nullptr;
		LastAttackDeltaTime = 0.0f;
	}
	else
	{
		LastAttackDeltaTime += DeltaTime;
	}
}
