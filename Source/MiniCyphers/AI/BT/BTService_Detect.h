// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MiniCyphersService.h"
#include "BTService_Detect.generated.h"

class UBehaviorTreeComponent;
class UMiniCyphersService;
/**
 * 
 */
UCLASS()
class MINICYPHERS_API UBTService_Detect : public UMiniCyphersService
{
	GENERATED_BODY()

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	bool TryGetOverlapResult(AMiniCyphersCharacter* Owner, TArray<FOverlapResult>& OverlapResults);
	bool TryGetOverlapTarget(AMiniCyphersCharacter* Owner, OUT AMiniCyphersCharacter*& FoundTarget);
	void SetDetectedTarget(UBehaviorTreeComponent& OwnerComp, AMiniCyphersCharacter* TargetCharacter);

private:
	UPROPERTY(EditAnywhere)
	float DetectRadius = 600.0f;
};
