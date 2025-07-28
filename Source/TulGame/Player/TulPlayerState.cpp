// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPlayerState.h"
#include "TulGame/GameModes/TulExperienceManagerComponent.h"

void ATulPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UTulExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UTulExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnTulExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void ATulPlayerState::OnExperienceLoaded(const UTulExperienceDefinition* CurrentExperience)
{
}
