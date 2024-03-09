// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersAnimNotifyState.h"
#include "AnimNotifyStiffCheckState.generated.h"

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UAnimNotifyStiffCheckState : public UMiniCyphersAnimNotifyState
{
	GENERATED_BODY()

protected:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	UPROPERTY(EditAnywhere)
	float StiffAnimationSpeedRate = 0.05f;
};
