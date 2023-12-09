// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include <Kismet/GameplayStatics.h>
#include "../MiniCyphersGameInstance.h"
#include "../MiniCyphersGameMode.h"
#include "../MiniCyphersPlayerState.h"

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

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnChangeHealth(int Amount)
{
	auto* GameMode = Cast<AMiniCyphersGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode == nullptr)
		return;

	GameMode->MyPlayerState->OnChangePlayerHealth(0, Amount);
}

