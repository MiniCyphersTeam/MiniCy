// Fill out your copyright notice in the Description page of Project Settings.


#include "Trooper.h"
#include "Kismet/GameplayStatics.h"
#include "../Character/HealthComponent.h"
#include "../AI/MiniCyphersAIController.h"


ATrooper::ATrooper()
{
	// AIControllerClass = BP�� �� ��Ƽ�� AI Controller�� �־��� ��
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ATrooper::OnUseNormalAttack()
{
	Super::OnUseNormalAttack();

	if (NormalAttackAnimA && NormalAttackAnimB)
	{
		PlayAnimMontage(bUseAnimA ? NormalAttackAnimA : NormalAttackAnimB);
		bUseAnimA = !bUseAnimA;
	}

	if (NormalTrooper)
	{
		UGameplayStatics::PlaySoundAtLocation(this, NormalTrooper, GetActorLocation());
	}
}

void ATrooper::OnUseRightClickAttack()
{
	Super::OnUseRightClickAttack();
	if (RightClickTrooper)
	{
		UGameplayStatics::PlaySoundAtLocation(this, RightClickTrooper, GetActorLocation());
	}
}

void ATrooper::OnUseShiftLeftClickAttack()
{
	Super::OnUseShiftLeftClickAttack();

	HealthComponent = FindComponentByClass<UHealthComponent>();
	if (HealthComponent)
	{
		HealthComponent->ChangeHealth(-20, true); //�̷����ϸ� �÷��̾�ƴ϶� ���Ͱ� ����..
	}
}

void ATrooper::OnUseQSkill()
{
	Super::OnUseQSkill();
	if (QSkillTrooper)
	{
		UGameplayStatics::PlaySoundAtLocation(this, QSkillTrooper, GetActorLocation());
	}
}

