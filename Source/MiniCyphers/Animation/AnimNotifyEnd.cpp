// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyEnd.h"
#include "../Character/MiniCyphersCharacter.h"
#include "../Character/ComboActionComponent.h"

void UAnimNotifyEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	TArray<UComboActionComponent*> ComboComponents = GetComboComponents(MeshComp);
	if (ComboComponents.IsEmpty())
		return;

	for (auto Component : ComboComponents)
	{
		Component->ResetCombo();
	}
}

TArray<UComboActionComponent*> UAnimNotifyEnd::GetComboComponents(USkeletalMeshComponent* MeshComp)
{
	TArray<UComboActionComponent*> ComboComponents;

	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return ComboComponents;

	owner->GetComponents<UComboActionComponent>(ComboComponents);

	return ComboComponents;
}

AMiniCyphersCharacter* UAnimNotifyEnd::GetCharacter(USkeletalMeshComponent* MeshComp)
{
	auto owner = MeshComp->GetOwner();
	if (owner == nullptr)
		return nullptr;

	return Cast<AMiniCyphersCharacter>(owner);
}
