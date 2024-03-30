// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShot.h"
#include "../TimeShotComponent.h"


ATowerShot::ATowerShot()
{
	TimeShotComponent = CreateDefaultSubobject<UTimeShotComponent>(TEXT("TimeShotComponent"));
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	RootComponent = StaticMesh;
}

void ATowerShot::SetAlpha(float alpha)
{
	if (StaticMesh)
	{
		// ���� �޽��� 0�� ���͸����� �����´�.
		if (MyMaterialInterface == nullptr)
		{
			MyMaterialInterface = StaticMesh->GetMaterial(0);
		}

		// ���̽� ���͸��� ������� ���� �ν��Ͻ��� ����
		if (MyMaterialInterfaceDynamic == nullptr)
		{
			MyMaterialInterfaceDynamic = UMaterialInstanceDynamic::Create(MyMaterialInterface, this);
		}

		if (MyMaterialInterfaceDynamic != nullptr)
		{
			// Transparency_Amount��� �̸��� �Ķ���� ���� ����
			CurrentTransparencyAmount = alpha;
			MyMaterialInterfaceDynamic->SetScalarParameterValue(TEXT("Transparency_Amount"), alpha);	
			MyMaterialInterfaceDynamic->SetVectorParameterValue("Base Color", WarningAreaColor);
		}

		// ����ƽ �޽� �� ���͸��� ���� �ν��Ͻ� ����
		StaticMesh->SetMaterial(0, MyMaterialInterfaceDynamic);
	}
}

void ATowerShot::ChangeAlpha(float DeltaAlpha)
{
	float NewAlpha = CurrentTransparencyAmount + DeltaAlpha;
	NewAlpha = NewAlpha > 0 ? NewAlpha : 0;
	NewAlpha = NewAlpha > 1 ? 1 : NewAlpha;
	SetAlpha(NewAlpha);
}

