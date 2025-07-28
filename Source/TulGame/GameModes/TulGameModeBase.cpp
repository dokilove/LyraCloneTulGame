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

	// ���� GameInstance�� ���� �ʱ�ȭ �۾��� ����ǹǷ�, �� �����ӿ��� Lyra�� Concept�� Experience ó���� ������ �� ����.
	// - �̸� ó���ϱ� ����, �� ������ �ڿ� �̺�Ʈ�� �޾� ó���� �̾ �����Ѵ�
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpectingOne);
}

void ATulGameModeBase::InitGameState()
{
	Super::InitGameState();

	// Experience �񵿱� �ε��� ���� Delegate�� �غ��Ѵ�
	UTulExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UTulExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	// OnExperienceLoaded ���
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
