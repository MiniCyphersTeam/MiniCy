// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include <Kismet/GameplayStatics.h>
#include "MiniCyphersCharacter.h"
#include "../MiniCyphersGameInstance.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersGameState.h"
#include "../MiniCyphersPlayerState.h"
#include "Shiva.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	auto* Data = GameMode->GetStatData(ECharacterType::Shiva);
	if (Data == nullptr)
		return;

	MaxHealth = Data->MaxHp;
	CurrentHealth = MaxHealth;
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::ChangeHealth(AMiniCyphersCharacter* Attacker, int Amount)
{
	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	if (CurrentHealth <= 0)
		return;

	//Shiva�̸鼭 bInvincible�� true�϶� ����  - ���� Ȯ��X
	AShiva* ShivaCharacter = Cast<AShiva>(GetOwner());
	if (ShivaCharacter && ShivaCharacter->bInvincible)
		return;

	CurrentHealth += Amount;

	auto Character = Cast<AMiniCyphersCharacter>(GetOwner());

	if (Character->IsPlayer()) // ���� �޴� �ְ� �÷��̾�
	{
		GameMode->MyPlayerState->OnChangePlayerHealth(0, CurrentHealth);
		UE_LOG(LogTemp, Warning, TEXT("Player's Current Health: %d"), CurrentHealth);
	}
	else
	{
		GameMode->MyGameState->OnChangedHealth(Character->CharacterId, CurrentHealth);
		UE_LOG(LogTemp, Warning, TEXT("Non Player Current Health: %f"), CurrentHealth);
	}

	if (Amount < 0)
	{
		if (CurrentHealth <= 0)
		{
			Character->OnDie();
		}
		else
		{
			Character->OnHit(Attacker);
		}

		OnDamaged.Broadcast(Attacker, CurrentHealth);
	}
}

