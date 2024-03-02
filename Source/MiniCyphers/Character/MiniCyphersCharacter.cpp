// Copyright Epic Games, Inc. All Rights Reserved.

#include "MiniCyphersCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "HealthComponent.h"
#include "Sentinel.h"
#include "Trooper.h"
#include "Kismet/GameplayStatics.h"
#include "ComboActionComponent.h"
#include "RandomMotionComponent.h"
#include "QuestComponent.h"
#include "HitDeadComponent.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AMiniCyphersCharacter

AMiniCyphersCharacter::AMiniCyphersCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	QuestComponent = CreateDefaultSubobject<UQuestComponent>(TEXT("UQuestComponent"));
	RandomMotionComponent = CreateDefaultSubobject<URandomMotionComponent>(TEXT("RandomMotionComponent"));
	HitDeadComponent = CreateDefaultSubobject<UHitDeadComponent>(TEXT("HitDeadComponent"));

	ActionComponentMap.Empty();
	for (int i = 0; i < (int)EAttackType::Max; i++)
	{
		auto AttackType = (EAttackType)i;

		FString AttackTypeStr = GetEnumNameAsString(AttackType);
		FString ComponentName = TEXT("ComboActionComponent [") + AttackTypeStr + "]";
		auto Component = CreateDefaultSubobject<UComboActionComponent>((FName)*ComponentName);
		ActionComponentMap.Add(AttackType, Component);

		ActionCoolTimeMap.Add(AttackType, 5.0f);
		CurrentActionCoolTimeMap.Add(AttackType, 0.0f);
	}
}

FString AMiniCyphersCharacter::GetEnumNameAsString(EAttackType EnumValue)
{
	switch (EnumValue)
	{
	case EAttackType::NormalAttack:
		return "NormalAttack";

	case EAttackType::RightClickAttack:
		return "RightAttack";

	case EAttackType::ShiftAttack:
		return "ShiftAttack";

	case EAttackType::QSkillAttack:
		return "QSkillAttack";

	case EAttackType::UltimateAttack:
		return "UltimateAttack";

	case EAttackType::GrabSkillAttack:
		return "GrabSkillAttack";
	}

	return "";
}

void AMiniCyphersCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentDeltaTime += DeltaTime;
}


void AMiniCyphersCharacter::Move(const FVector2D Value)
{
	if (isDead)
		return;

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Value.Y);
		AddMovementInput(RightDirection, Value.X);
	}
}

void AMiniCyphersCharacter::Look(const FVector2D Value)
{
	if (isDead)
		return;

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Value.X);
		AddControllerPitchInput(Value.Y);
	}
}

bool AMiniCyphersCharacter::CheckCoolTime(EAttackType AttackType)
{
	if (ActionCoolTimeMap.Contains(AttackType) == false)
		return true;

	if (CurrentActionCoolTimeMap.Contains(AttackType) == false)
		return true;

	float CurrentCoolTime = CurrentActionCoolTimeMap[AttackType];
	return CurrentCoolTime <= CurrentDeltaTime;
}

void AMiniCyphersCharacter::UseSkill(EAttackType AttackType) //ĳ����(��)�� ����
{
	if (isDead)
		return;

	if (isProgressingSkillMotion)
		return;

	if (ActionComponentMap.Contains(AttackType) == false)
		return;

	if (ActionCoolTimeMap.Contains(AttackType) == false)
		return;

	for (auto& MapPair : ActionComponentMap)
	{
		if (MapPair.Key == AttackType)
			continue;

		MapPair.Value->ResetCombo();
	}

	ActionComponentMap[AttackType]->DoCombo();
	CurrentActionCoolTimeMap[AttackType] = CurrentDeltaTime + ActionCoolTimeMap[AttackType];

	switch (AttackType)
	{
	case EAttackType::NormalAttack:
		OnUseNormalAttack();
		break;

	case EAttackType::RightClickAttack:
		OnUseRightClickAttack();
		break;

	case EAttackType::ShiftAttack:
		OnUseShiftLeftClickAttack();
		break;

	case EAttackType::QSkillAttack:
		OnUseQSkill();
		break;

	case EAttackType::UltimateAttack:
		OnUseUltimateSkill();
		break;

	case EAttackType::GrabSkillAttack:
		OnUseGrabSkill();
		break;
	}

	isProgressingSkillMotion = true;
}

void AMiniCyphersCharacter::OnFinishedSkillMotion(EAttackType AttackType)
{
	isProgressingSkillMotion = false;
	OnUseSkillDelegate.Broadcast(AttackType);
}

void AMiniCyphersCharacter::OnHit(AMiniCyphersCharacter* Attacker, EDamageType DamageType, int DamageAmount, float UpperVelocity, float KnockBackDistance, bool isMelee)
{
	if (isDead)
		return;

	if (!bSuperArmor && DamageType == EDamageType::Airborne)
	{
		GetCharacterMovement()->JumpZVelocity = UpperVelocity;
		Jump();
	}

	if (!bSuperArmor)
	{
		Move(FVector2D(0, -KnockBackDistance));
	}

	SetAnimationSpeedRate(0.5f);

	if (HitDeadComponent)
	{
		HitDeadComponent->PlayHitMontage(DamageType);
	}
}

void AMiniCyphersCharacter::OnDie()
{
	if (isDead)
		return;

	isDead = true;

	if (HitDeadComponent)
	{
		HitDeadComponent->PlayDeadMontage();
	}
}

bool AMiniCyphersCharacter::IsPlayer()
{
	return Controller->IsPlayerController() || isPlayerTeam;
}

FVector AMiniCyphersCharacter::GetLookVector(AMiniCyphersCharacter*& Target) const
{
	return Target->GetActorLocation() - GetActorLocation();
}

void AMiniCyphersCharacter::RotateToTarget(AMiniCyphersCharacter*& Target, float RotationSpeed)
{
	if (Target == nullptr)
		return;

	FVector LookVector = GetLookVector(Target);
	LookVector.Z = 0.f;

	FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
	SetRotation(TargetRotation, RotationSpeed);
}

void AMiniCyphersCharacter::SetRotation(FRotator Rotation, float RotationSpeed)
{
	FRotator TargetRotation = FMath::RInterpTo(GetActorRotation(), Rotation, GetWorld()->GetDeltaSeconds(), RotationSpeed);
	SetActorRotation(TargetRotation);
}

FVector AMiniCyphersCharacter::GetTargetPosition(ECollisionChannel Channel, float RayCastDistance, OUT bool& IsFoundTarget)
{
	IsFoundTarget = false;
	return FVector::ZeroVector;
}

bool AMiniCyphersCharacter::IsSatisfiedNormalAttack()
{
	return CheckCoolTime(EAttackType::NormalAttack) && !isDead;
}

bool AMiniCyphersCharacter::IsSatisfiedRightClickAttack()
{
	return CheckCoolTime(EAttackType::RightClickAttack) && !isDead;
}

bool AMiniCyphersCharacter::IsSatisfiedQSkill()
{
	return CheckCoolTime(EAttackType::QSkillAttack) && !isDead;
}

bool AMiniCyphersCharacter::IsSatisfiedUltimateSkill()
{
	return CheckCoolTime(EAttackType::UltimateAttack) && !isDead;
}

bool AMiniCyphersCharacter::IsSatisfiedGrabSkill()
{
	return CheckCoolTime(EAttackType::GrabSkillAttack) && !isDead;
}

bool AMiniCyphersCharacter::IsSatisfiedShiftAttack()
{
	return CheckCoolTime(EAttackType::ShiftAttack) && !isDead;
}

void AMiniCyphersCharacter::OnUseNormalAttack()
{
	if (RandomMotionComponent)
	{
		RandomMotionComponent->NormalRandomAttack();
	}
}

bool AMiniCyphersCharacter::TryGetOverlapResult(AMiniCyphersCharacter* Character, TArray<FOverlapResult>& OverlapResults)
{
	auto* World = Character->GetWorld();
	if (World == nullptr)
		return false;

	FVector Center = Character->GetActorLocation();
	FCollisionQueryParams CollisionParam(NAME_None, false, Character);

	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_Pawn,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionParam);

	if (bResult)
	{
		DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
	}

	return bResult;
}

bool AMiniCyphersCharacter::TryGetOverlapTargets(AMiniCyphersCharacter* Character, OUT TArray<AMiniCyphersCharacter*>& FoundTargets)
{
	TArray<FOverlapResult> OverlapResults;

	if (TryGetOverlapResult(Character, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = Cast<AMiniCyphersCharacter>(OverlapResult.GetActor());
			if (TargetCharacter == nullptr)
				continue;

			if (IsPlayer() != TargetCharacter->IsPlayer())
			{
				FoundTargets.Add(TargetCharacter);
				continue;
			}
		}
	}

	return FoundTargets.Num() > 0;
}

bool AMiniCyphersCharacter::TryGetOverlapTarget(AMiniCyphersCharacter* Character, OUT AMiniCyphersCharacter*& FoundTarget)
{
	TArray<FOverlapResult> OverlapResults;

	if (TryGetOverlapResult(Character, OverlapResults))
	{
		for (auto const& OverlapResult : OverlapResults)
		{
			auto* TargetCharacter = Cast<AMiniCyphersCharacter>(OverlapResult.GetActor());
			if (TargetCharacter == nullptr)
				continue;

			if (IsPlayer() != TargetCharacter->IsPlayer())
			{
				FoundTarget = TargetCharacter;
				break;
			}
		}
	}

	return FoundTarget != nullptr;
}

void AMiniCyphersCharacter::SetAnimationSpeedRate(float Rate)
{
	auto* MyMesh = GetMesh();
	if (MyMesh == nullptr)
		return;

	auto* AnimInstance = MyMesh->GetAnimInstance();
	if (AnimInstance == nullptr)
		return;

	auto* CurrentMontange = AnimInstance->GetCurrentActiveMontage();
	if (CurrentMontange == nullptr)
		return;

	AnimInstance->Montage_SetPlayRate(CurrentMontange, Rate);
}
