// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShot.h"


ATowerShot::ATowerShot()
{
	TimeShotComponent = CreateDefaultSubobject<UTimeShotComponent>(TEXT("TimeShotComponent"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	RootComponent = StaticMesh;
}

void ATowerShot::BeginPlay()
{
	Super::BeginPlay();
	SetAlpha(1.0f);
}

void ATowerShot::SetAlpha(float alpha)
{
	if (StaticMesh)
	{
		// ���� �޽��� 0�� ���͸����� �����´�.
		auto* BaseMaterial = StaticMesh->GetMaterial(0);

		// ���̽� ���͸��� ������� ���� �ν��Ͻ��� ����
		auto* DynamicMaterialInstance = UMaterialInstanceDynamic::Create(BaseMaterial, this);
		if (DynamicMaterialInstance)
		{
			// Transparency_Amount��� �̸��� �Ķ���� ���� ����
			DynamicMaterialInstance->SetScalarParameterValue(TEXT("Transparency_Amount"), alpha);
		}

		CurrentTransparencyAmount = alpha;
		// ����ƽ �޽� �� ���͸��� ���� �ν��Ͻ� ����
		StaticMesh->SetMaterial(0, DynamicMaterialInstance);
	}
}

void ATowerShot::ChangeAlpha(float DeltaAlpha)
{
	float NewAlpha = CurrentTransparencyAmount + DeltaAlpha;
	NewAlpha = NewAlpha > 0 ? NewAlpha : 0;
	NewAlpha = NewAlpha > 1 ? 1 : NewAlpha;
	SetAlpha(NewAlpha);
}

