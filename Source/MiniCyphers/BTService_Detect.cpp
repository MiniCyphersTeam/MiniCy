// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_Detect.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "MiniCyphersCharacter.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MiniCyphersAIController.h"

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto* MyCharacter = GetCharacter(OwnerComp);
	if (MyCharacter == nullptr)
		return;

	AMiniCyphersCharacter* DetectedTarget = nullptr;
	TryGetOverlapTarget(MyCharacter, OUT DetectedTarget);

	SetDetectedTarget(OwnerComp, DetectedTarget);
}

bool UBTService_Detect::TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults)
{
	auto* World = Owner->GetWorld();
	if (World == nullptr)
		return false;

	FVector Center = Owner->GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, Owner);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionParam);

	if (bResult)
	{
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	}
	
	return bResult;
}

bool UBTService_Detect::TryGetOverlapTarget(AMiniCyphersCharacter* Owner, OUT AMiniCyphersCharacter*& FoundTarget)
{
	TArray<FOverlapResult> OverlapResults;
	bool bResult = false;

	if (TryGetOverlapResult(Owner, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = GetCharacter(OverlapResult);
			if (TargetCharacter == nullptr)
				continue;

			if (TargetCharacter->IsPlayer() == false)
				continue;

			bResult = true;
			FoundTarget = TargetCharacter;
			break;
		}
	}

	return bResult;
}

void UBTService_Detect::SetDetectedTarget(UBehaviorTreeComponent& OwnerComp, AMiniCyphersCharacter* TargetCharacter)
{
	auto* BlackBoard = GetBlackboardComponent(OwnerComp);
	if (BlackBoard == nullptr)
		return;

	BlackBoard->SetValueAsObject(AMiniCyphersAIController::TargetObjectKey, TargetCharacter);

	if (TargetCharacter != nullptr)
	{
		BlackBoard->SetValueAsVector(AMiniCyphersAIController::PatrolPosKey, TargetCharacter->GetActorLocation());
	}
}