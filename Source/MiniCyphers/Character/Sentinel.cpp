// Fill out your copyright notice in the Description page of Project Settings.


#include "Sentinel.h"
#include "Kismet/GameplayStatics.h"
#include "../AI/MiniCyphersAIController.h"


ASentinel::ASentinel()
{
	// AIControllerClass = BP�� �� ��Ƽ�� AI Controller�� �־��� ��
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

void ASentinel::OnUseNormalAttack()
{
	Super::OnUseNormalAttack();
	if (NormalSentinel)
	{
		UGameplayStatics::PlaySoundAtLocation(this, NormalSentinel, GetActorLocation());
	}

}
