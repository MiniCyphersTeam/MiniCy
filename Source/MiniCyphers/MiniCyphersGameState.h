// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MiniCyphersGameState.generated.h"

UENUM(BlueprintType)
enum class ESpawnType : uint8
{
	Sentinel,
	Trooper,
	Tower,
};


/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	// ����Ʈ, Ÿ�̸�, HP, ���, ���̺� �ܰ�, ���� ���� ����˴ϴ�.

	// ���⼭�� ������ �׾����� �� ���� �̷������� �Ϸ��� hp�� �ʿ��Ѱ�

public:
	AMiniCyphersGameState();

private:
	int TrooperCharacterId = 0;
	int TowerCharacterId = 1;

	int StartSentinelCharacterId = 2;
	int CurrentSentinelCharacterId = 2;

private:
	UPROPERTY(EditAnywhere)
	TArray<FVector> SentinelSpawnPositions;

	UPROPERTY(EditAnywhere)
	FRotator SentinelSpawnRotation;

	UPROPERTY(EditAnywhere)
	FVector TrooperSpawnPosition;

	UPROPERTY(EditAnywhere)
	FRotator TrooperSpawnRotation;

	UPROPERTY(EditAnywhere)
	FVector TowerSpawnPosition;

	UPROPERTY(EditAnywhere)
	FRotator TowerSpawnRotation;

private:
	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class AMiniCyphersCharacter> TrooperClass;

	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class AMiniCyphersCharacter> TowerClass;

	UPROPERTY(EditAnywhere, Category = Character)
	TSubclassOf<class AMiniCyphersCharacter> SentinelClass;

private:
	TMap<int, int> MonsterHealthMap;
	int MaxFieldSentinelCount = 2;
	int CurrentSpawnSentinelPositionIndex = 0;

public:
	void OnChangedHealth(int ObjectID, float CurrentHealth);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	int GetDeadSentinelCount();
	bool IsDeadTrooper();
	bool IsDeadTower();

private:
	void Spawn(ESpawnType SpawnType);
};
