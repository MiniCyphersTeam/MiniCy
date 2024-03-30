// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersAnimNotifyState.h"
#include "AnimNotifySummonState.generated.h"

UENUM()
enum class ESummonType
{
	None = -1,
	ShivaKnife = 0, // �ù� ��Ÿ ������
	TrooperStone = 1, // ������ ���� ��ų ��
	BombSentinel = 2, // ��ź ��Ƽ��
	BombSentinelBomb = 3, // ��ź ��Ƽ���� ���� ����
};

class AMiniCyphersCharacter;
class AShiva;
class ATrooper;
class ABombSentinel;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifySummonState : public UMiniCyphersAnimNotifyState
{
	GENERATED_BODY()
	
private:
	void SummonObject(AMiniCyphersCharacter* Character);
	void SummonTrooperStone(ATrooper* TrooperCharacter);
	void SummonShivaKnife(AShiva* ShivaCharacter);
	void SummonBombSentinel(ATrooper* TrooperCharacter);
	void SummonBombSentinelBomb(ABombSentinel* BombSentinel);

	UPROPERTY(EditAnywhere)
	ESummonType SummonType;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AMiniCyphersProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Projectile)
	TSubclassOf<class AMiniCyphersCharacter> SummonCharacterClass;

	UPROPERTY(EditAnywhere)
	TArray<FVector> TrooperSummonOffsetArray;

protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

};
