// Fill out your copyright notice in the Description page of Project Settings.


#include "ShivaNormalAttackProjectile.h"
#include "../MiniCyphersCharacter.h"
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
	ProjectileMovementComp->InitialSpeed = 2000.f;
	ProjectileMovementComp->MaxSpeed = 2000.f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->bShouldBounce = false;

	// Die after 1 seconds by default
	InitialLifeSpan = 0.5f;

}

void AShivaNormalAttackProjectile::BeginPlay()
{
	
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
	AMiniCyphersCharacter* MiniCyphersCharacter = Cast<AMiniCyphersCharacter>(OtherActor);
	if ((OtherComp != nullptr) && MiniCyphersCharacter != nullptr)
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation()); //��� �߰��ϴ� �ڵ��ε� ������ �ʿ� ��� �ϴ� ��Ȱ��ȭ �ص�

		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			//const FRotator SpawnRotation = GetActorRotation();
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			//const FVector SpawnLocation = GetActorLocation();

			//Set Spawn Collision Handling Override
			//FActorSpawnParameters ActorSpawnParams;
			//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			/*if (DamagedEffect != nullptr)
			{
				World->SpawnActor<AProjectileEffect>(DamagedEffect, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}*/

				
			MiniCyphersCharacter->OnHit(ProjectileOwner);


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
	ProjectileOwner = Character;
}
