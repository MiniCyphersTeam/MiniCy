// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"
#include "../AI/MiniCyphersAIController.h"

ATower::ATower()
{
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ATower::BeginPlay()
{
	bSuperArmor = true; // Ÿ���� �׽� ���۾Ƹ�
	IsPlayerTeam = true; // �÷��̾� ��
}

// Ÿ���� ���� ����� ���� Ž���Ѵ�.
AMiniCyphersCharacter* ATower::GetTarget()
{
	AMiniCyphersCharacter* Target;

	if (TryGetOverlapTarget(this, OUT Target) == false)
		return nullptr;

	return Target;
}