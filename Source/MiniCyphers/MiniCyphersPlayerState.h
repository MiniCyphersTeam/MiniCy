// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MiniCyphersPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHPChangedDelegate, int, float)

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
	void OnChangePlayerHealth(int objectId, float Amount);

private:
	float CurrentHP;

	// ����, HP, ���, ����, �̴ϸ� ��ġ ���� ����˴ϴ�.
};
