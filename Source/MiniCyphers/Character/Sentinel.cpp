// Fill out your copyright notice in the Description page of Project Settings.


#include "Sentinel.h"
#include "../AI/MiniCyphersAIController.h"

ASentinel::ASentinel()
{
	// AIControllerClass = BP로 된 센티넬 AI Controller를 넣어줄 것
	AIControllerClass = AMiniCyphersAIController::StaticClass();
}
