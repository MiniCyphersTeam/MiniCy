// Fill out your copyright notice in the Description page of Project Settings.


#include "BombSentinel.h"
#include "Tower.h"
#include "Components/CapsuleComponent.h"


void ABombSentinel::BeginPlay()
{
	Super::BeginPlay();

	bSuperArmor = true;
	IsPlayerTeam = false;
}

// ������ Ÿ��
void ABombSentinel::UpdateTarget()
{
	TArray<AMiniCyphersCharacter*> Targets;

	if (TryGetOverlapTargets(this, OUT Targets) == false)
		return;

	for (auto& Target : Targets)
	{
		auto* Tower = Cast<ATower>(Target);
		if (Tower == nullptr)
			continue;

		DetectedTarget = Tower;
	}
}
