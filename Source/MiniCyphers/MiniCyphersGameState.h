// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MiniCyphersGameState.generated.h"

USTRUCT(BlueprintType)
struct FQuestPhaseData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FQuestPhaseData() {}

	UPROPERTY()
	int32 QuestId;

	UPROPERTY()
	int32 PhaseNumber;
};

USTRUCT(BlueprintType)
struct FQuestData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FQuestData() {}

	UPROPERTY()
	int32 QuestId;

	UPROPERTY()
	FString Description;

	UPROPERTY()
	int32 MaxProgress;
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnChangedQuestDelegate, TArray<FQuestData*>, TMap<int, int>)

/**
 * 
 */
UCLASS()
class MINICYPHERS_API AMiniCyphersGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	// ����Ʈ, Ÿ�̸�, HP, ���, ���̺� �ܰ�, ���� ���� ����˴ϴ�.

	//���⼭�� ������ �׾����� �� ���� �̷������� �Ϸ��� hp�� �ʿ��Ѱ�

private:
	// Quest Id - Progress
	TMap<int, int> QuestProgressDatas;
	int CurrentPhaseNumber = -1;

private:

	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* QuestPhaseTable;

	UPROPERTY(EditAnywhere, Category = Data)
	class UDataTable* QuestTable;

public:
	TArray<FQuestPhaseData*> GetQuestPhaseDatas(int PhaseNumber);
	FQuestData* GetQuestData(int QuestId);
	TArray<FQuestData*> GetQuestDatas(int PhaseNumber);


public:
	bool TryChangePhase(int PhaseNumber);
	void OnChangedPhase(int PhaseNumber);

	bool TryCompleteQuest(int QuestId);
	void OnChangedQuest(int QuestId);

	FOnChangedQuestDelegate OnChangedQuestDelegate;

public:
	void OnChangedHealth(int ObjectID, float Amount);
};
