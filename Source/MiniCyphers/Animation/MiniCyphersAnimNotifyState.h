// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "MiniCyphersAnimNotifyState.generated.h"

class AMiniCyphersCharacter;
class UHealthComponent;

/**
 * 
 */
UCLASS()
class MINICYPHERS_API UMiniCyphersAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;

public:
	AMiniCyphersCharacter* GetCharacter(const FOverlapResult& OverlapResult);
	AMiniCyphersCharacter* GetCharacter(USkeletalMeshComponent* MeshComp);
	UHealthComponent* GetHealthComponent(USkeletalMeshComponent* MeshComp);

};
