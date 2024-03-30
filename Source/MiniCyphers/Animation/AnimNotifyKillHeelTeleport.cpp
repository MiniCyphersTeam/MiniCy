// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifyKillHeelTeleport.h"
#include "../Character/MiniCyphersCharacter.h"

void UAnimNotifyKillHeelTeleport::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
    Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

    IsFoundTarget = false;
    FindTarget(MeshComp);
}

void UAnimNotifyKillHeelTeleport::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{    
    Super::NotifyEnd(MeshComp, Animation, EventReference);

    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (!MyCharacter)
        return;

    // �ڷ���Ʈ �� ���� ��� ��� ĵ������ �ʵ��� �����
    /* if (!IsFoundTarget)
    {
        MyCharacter->StopAnimMontage();
        MyCharacter->OnFinishedSkillMotion(EAttackType::ShiftAttack);
    }*/
}

FVector UAnimNotifyKillHeelTeleport::FindTarget(USkeletalMeshComponent* MeshComp)
{
    FVector ResultTargetLocation = FVector::ZeroVector;

    AMiniCyphersCharacter* MyCharacter = Cast<AMiniCyphersCharacter>(MeshComp->GetOwner());
    if (MyCharacter == nullptr)
        return ResultTargetLocation;

    auto AttackTargetLocation = MyCharacter->GetTargetPosition(ECollisionChannel::ECC_GameTraceChannel2, MoveDistance, IsFoundTarget);
    if (IsFoundTarget)
    {
        ResultTargetLocation = FVector(AttackTargetLocation.X, AttackTargetLocation.Y, CurrentLocation.Z);;
    }
    else
    {
        bool NoUseFoundTarget = false;
        auto Location = MyCharacter->GetTargetPosition(ECollisionChannel::ECC_WorldStatic, MoveDistance, NoUseFoundTarget);
        ResultTargetLocation = FVector(Location.X, Location.Y, CurrentLocation.Z);
    }

    return ResultTargetLocation;
}
