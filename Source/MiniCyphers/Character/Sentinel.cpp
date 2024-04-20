// Fill out your copyright notice in the Description page of Project Settings.


#include "Sentinel.h"
#include "Kismet/GameplayStatics.h"
#include "../AI/MiniCyphersAIController.h"
#include "Tower.h"

 
ASentinel::ASentinel()
{
	// AIControllerClass = BP�� �� ��Ƽ�� AI Controller�� �־��� ��
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ASentinel::BeginPlay()
{
	Super::BeginPlay();
	
	bSuperArmor = false; // ��Ƽ���� ���۾Ƹ� ����
	IsPlayerTeam = false; // �� ��
}

void ASentinel::OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, float StiffTime, int HealthAmount, float UpperVelocity, float KnockBackDistance, bool isMelee)
{
	Super::OnHit(Attacker, DamageType, StiffTime, HealthAmount, UpperVelocity, KnockBackDistance, isMelee);
}
