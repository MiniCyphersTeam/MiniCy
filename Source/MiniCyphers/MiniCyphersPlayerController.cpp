// Fill out your copyright notice in the Description page of Project Settings.


#include "MiniCyphersPlayerController.h"
#include "Character/MiniCyphersCharacter.h"
#include "MiniCyphersPlayerState.h"

void AMiniCyphersPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AMiniCyphersPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	OnPossessCharacter(Cast<AMiniCyphersCharacter>(aPawn));
}

void AMiniCyphersPlayerController::OnPossessCharacter(AMiniCyphersCharacter* aCharacter)
{

}

AMiniCyphersPlayerState* AMiniCyphersPlayerController::GetState()
{
	return Cast<AMiniCyphersPlayerState>(PlayerState);
}
