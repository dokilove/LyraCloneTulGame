// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPlayerState.h"
#include "TulGame/GameModes/TulExperienceManagerComponent.h"
#include "TulGame/GameModes/TulGameModeBase.h"

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
	if (ATulGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATulGameModeBase>())
	{
		// ATulGameModeBase에서 GetPawnDataForController를 구현해야 함
		// - GetPawnDataForController에서 우리는 아직 PawnData를 설정하지 않았으므로, ExperienceManagerComponent의 DefaultPawnData로 설정한다
		const UTulPawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}

void ATulPlayerState::SetPawnData(const UTulPawnData* InPawnData)
{
	check(InPawnData);

	// PawnData가 두번 설정되는 것은 원하지 않음
	check(!PawnData);

	PawnData = InPawnData;
}
