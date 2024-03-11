// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerShot.h"


ATowerShot::ATowerShot()
{
	TimeShotComponent = CreateDefaultSubobject<UTimeShotComponent>(TEXT("TimeShotComponent"));
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UStaticMeshComponent"));
	
	// �̰����� ��Ʈ�� �����ϱ� ������ Ʈ�������� ������ �� ����
	RootComponent = StaticMesh;

	// Ʈ�������� �����ϰ� �ʹٸ�, ������ Static Mesh�� CreateDefaultSubobject�� ���� �����,
	// BP���� ���� ��ġ ���� ���ϸ� ��
	// �׷� �翬�� �Ʒ� BeginPlay �ڵ� ���뵵 StaticMesh���� ShotMesh ������ �ٲ��� ��

}

void ATowerShot::BeginPlay()
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
			DynamicMaterialInstance->SetScalarParameterValue(TEXT("Transparency_Amount"), 0.1f);
		}

		// ����ƽ �޽� �� ���͸��� ���� �ν��Ͻ� ����
		StaticMesh->SetMaterial(0, DynamicMaterialInstance);
	}
}

