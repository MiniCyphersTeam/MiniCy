// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimNotifyMoveState.h"
#include "AnimNotifyJumpState.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyJumpState : public UAnimNotifyMoveState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
};
