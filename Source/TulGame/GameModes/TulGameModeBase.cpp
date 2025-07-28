// Fill out your copyright notice in the Description page of Project Settings.


#include "TulGameModeBase.h"
#include "TulExperienceManagerComponent.h"
#include "TulGameState.h"
#include "TulGame/TulLogChannels.h"
#include "TulGame/Character/TulCharacter.h"
#include "TulGame/Player/TulPlayerController.h"
#include "TulGame/Player/TulPlayerState.h"

ATulGameModeBase::ATulGameModeBase()
{
	GameStateClass = ATulGameState::StaticClass();
	PlayerControllerClass = ATulPlayerController::StaticClass();
	PlayerStateClass = ATulPlayerState::StaticClass();
	DefaultPawnClass = ATulCharacter::StaticClass();
}

void ATulGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	// 아직 GameInstance를 통해 초기화 작업이 진행되므로, 현 프레임에는 Lyra의 Concept인 Experience 처리를 진행할 수 없다.
	// - 이를 처리하기 위해, 한 프레임 뒤에 이벤트를 받아 처리를 이어서 진행한다
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void ATulGameModeBase::InitGameState()
{
	Super::InitGameState();

	// Experience 비동기 로딩을 위한 Delegate를 준비한다
	UTulExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UTulExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	// OnExperienceLoaded 등록
	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnTulExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void ATulGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}

APawn* ATulGameModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	UE_LOG(LogTul, Log, TEXT("SpawnDefaultPawnAtTransform_Implementation is called!"));
	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void ATulGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{

}

bool ATulGameModeBase::IsExperienceLoaded() const
{
	check(GameState);
	UTulExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UTulExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	return ExperienceManagerComponent->IsExperienceLoaded();
}

void ATulGameModeBase::OnExperienceLoaded(const UTulExperienceDefinition* CurrentExperience)
{
}
