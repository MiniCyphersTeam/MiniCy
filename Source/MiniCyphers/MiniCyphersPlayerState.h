// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MiniCyphersPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, int, int)

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMiniCyphersPlayerState();

public:
	FOnHPChangedDelegate OnPlayerHPChanged;

public:
	void OnChangePlayerHealth(int objectId, int Amount);

private:
	float CurrentHP;

	// 레벨, HP, 목숨, 버프, 미니맵 위치 등이 저장됩니다.
};
