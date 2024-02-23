// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyDisappear.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/InputBlockComponent.h"

void UAnimNotifyDisappear::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	
}

void UAnimNotifyDisappear::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	// ������ȭ
}

void UAnimNotifyDisappear::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return;

	owner->Destroy();
}

