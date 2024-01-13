// Fill out your copyright notice in the Description page of Project Settings.


#include "ShivaNormalAttackProjectile.h"
#include "../MiniCyphersCharacter.h"
#include "../HealthComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AShivaNormalAttackProjectile::AShivaNormalAttackProjectile()
{

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));

	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AShivaNormalAttackProjectile::OnAttack);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	//Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovementComp->UpdatedComponent = CollisionComp;
	ProjectileMovementComp->InitialSpeed = 5000.f;
	ProjectileMovementComp->MaxSpeed = 5000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;

	// Die after 1 seconds by default
	InitialLifeSpan = 3.0f;

}

void AShivaNormalAttackProjectile::BeginPlay()
{
	Super::BeginPlay();	
	//InitVelocity()
}

void AShivaNormalAttackProjectile::Tick(float DeltaTime)
{

}

// ������Ÿ���� �ӵ��� �߻� �������� �ʱ�ȭ��Ű�� �Լ��Դϴ�.
void AShivaNormalAttackProjectile::InitVelocity(const FVector& ShootDirection)
{
	ProjectileMovementComp->Velocity = ShootDirection * ProjectileMovementComp->InitialSpeed;
}

void AShivaNormalAttackProjectile::OnAttack(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMiniCyphersCharacter* DamagedCharacter = Cast<AMiniCyphersCharacter>(OtherActor); //����ü�� ���� ��
	if ((OtherComp != nullptr) && DamagedCharacter != nullptr)
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation()); //��� �߰��ϴ� �ڵ��ε� ������ �ʿ� ��� �ϴ� ��Ȱ��ȭ �ص�

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
							
			DamagedCharacter->OnHit(ProjectileOwner); //�̰� �ĸ��� �� �ִϸ��̼� �����

			UHealthComponent* DamagedHealthComponent = DamagedCharacter->FindComponentByClass<UHealthComponent>();
			if (DamagedHealthComponent == nullptr)
				return;

			DamagedHealthComponent->ChangeHealth(-10, false);
			UE_LOG(LogTemp, Warning, TEXT("NonPlayer's current health: %d"), DamagedHealthComponent->GetCurrentHealth());


			// ���� �� > �Ѿ��� ��򰡿� �¾���(�Ȼ������) > ���� ��ü�� �����ͼ� > ���� ��ü�� �������ִ¾ָ� > �������� �� 
			// OnFire > OnHit > HitResult.GetActor > if(Damagable) > HitResult�� TakeDamage ȣ��

		}
	}
}


AController* AShivaNormalAttackProjectile::SetCharacterController(AController* Controller)
{
	CharacterController = Controller;
	return CharacterController;
}

void AShivaNormalAttackProjectile::SetProjectileOwner(AMiniCyphersCharacter* Character)
{
	ProjectileOwner = Character; //������
}
