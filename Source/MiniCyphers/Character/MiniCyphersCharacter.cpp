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


void AMiniCyphersCharacter::Move(const FVector2D Value)
{
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
	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Value.X);
		AddControllerPitchInput(Value.Y);
	}
}

void AMiniCyphersCharacter::UseSkill(EAttackType AttackType) //ĳ����(��)�� ����
{
	if (ActionComponentMap.Contains(AttackType) == false)
		return;

	for (auto& MapPair : ActionComponentMap)
	{
		if (MapPair.Key == AttackType)
			continue;

		MapPair.Value->ResetCombo();
	}

	ActionComponentMap[AttackType]->DoCombo();
	
	/*
	if (SoundComponentMap.Contains(AttackType) == false)
		return;

	SoundComponentMap[AttackType]->PlaySoundEffect();*/

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

	//useskill �� attacktype�� �޾Ƽ�, �׼�������Ʈ��(=�޺��׼�������Ʈ)�� ����Ÿ���� ������ ������... �´� �� ����

}

void AMiniCyphersCharacter::OnFinishedSkillMotion(EAttackType AttackType)
{
	OnUseSkillDelegate.Broadcast(AttackType);
}

bool AMiniCyphersCharacter::IsSatisfiedNormalAttack()
{
	return bCanAttack;
}

bool AMiniCyphersCharacter::IsSatisfiedRightClickAttack()
{
	return bCanAttack;
}

bool AMiniCyphersCharacter::IsSatisfiedQSkill()
{
	return bCanAttack;
}

bool AMiniCyphersCharacter::IsSatisfiedShiftAttack()
{
	return bCanAttack;
}

void AMiniCyphersCharacter::OnHit(AMiniCyphersCharacter* Attacker) //ĳ����(��)�� �ĸ���. Attack=������
{
	if (HitDeadComponent)
	{
		HitDeadComponent->PlayHitMontage();
	}
}

void AMiniCyphersCharacter::OnDie() //������ �ִϸ��̼�
{
	//PlayAnimMontage(DeathMontage, 1.0f);
	if (HitDeadComponent)
	{
		HitDeadComponent->PlayDeadMontage();
	}
}

bool AMiniCyphersCharacter::IsPlayer()
{
	return Controller->IsPlayerController();
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

void AMiniCyphersCharacter::OnUseNormalAttack()
{
	if (RandomMotionComponent)
	{
		RandomMotionComponent->NormalRandomAttack();
	}
}