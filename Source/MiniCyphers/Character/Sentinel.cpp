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
	
	// ��Ƽ���� �ʱ� ���۾Ƹ� ����
	bSuperArmor = false;
}