// Fill out your copyright notice in the Description page of Project Settings.


#include "Trooper.h"
#include "../AI/MiniCyphersAIController.h"


ATrooper::ATrooper()
{
	// AIControllerClass = BP�� �� ��Ƽ�� AI Controller�� �־��� ��
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}

