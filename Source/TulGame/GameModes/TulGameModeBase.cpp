// Fill out your copyright notice in the Description page of Project Settings.


#include "TulGameModeBase.h"
#include "TulExperienceManagerComponent.h"
#include "TulExperienceDefinition.h"
#include "TulGameState.h"
#include "TulGame/TulLogChannels.h"
#include "TulGame/Character/TulCharacter.h"
#include "TulGame/Player/TulPlayerController.h"
#include "TulGame/Player/TulPlayerState.h"
#include "TulGame/Character/TulPawnData.h"

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

UClass* ATulGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	// GetPawnDataForController를 활용하여, PawnData로부터 PawnClass를 유도하자
	if (const UTulPawnData* PawnData = GetPawnDataForController(InController))
	{
		if (PawnData->PawnClass)
		{
			return PawnData->PawnClass;
		}
	}

	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

PRAGMA_DISABLE_OPTIMIZATION
void ATulGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	if (IsExperienceLoaded())
	{
		Super::HandleStartingNewPlayer_Implementation(NewPlayer);
	}
}
PRAGMA_ENABLE_OPTIMIZATION

APawn* ATulGameModeBase::SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform)
{
	UE_LOG(LogTul, Log, TEXT("SpawnDefaultPawnAtTransform_Implementation is called!"));
	return Super::SpawnDefaultPawnAtTransform_Implementation(NewPlayer, SpawnTransform);
}

void ATulGameModeBase::HandleMatchAssignmentIfNotExpectingOne()
{
	// 해당 함수에서는 우리가 로딩할 Experience에 대해 PrimaryAssetId를 생성하여, OnMatchAssignmentGiven으로 넘겨준다

	FPrimaryAssetId ExperienceId;

	// precedence order (highest wins)
	// - matchmaking assignment (if present)
	// - default experience

	UWorld* World = GetWorld();

	// fall back to the default experience
	// 일단 기본 옵션으로 default하게 B_TulDefaultExperience로 설정해놓자
	if (!ExperienceId.IsValid())
	{
		ExperienceId = FPrimaryAssetId(FPrimaryAssetType("TulExperienceDefinition"), FName("B_TulDefaultExperience"));
	}

	// 필자가 이해한 HandleMatchAssignmentIfNotExpectingOne과 OnMatchAssignmentGiven()은 아직 직관적으로 이름이 와닫지 않는다고 생각한다
	// - 후일, 어느정도 Lyra가 구현되면, 해당 함수의 명을 더 이해할 수 있을 것으로 예상한다
	OnMatchAssignmentGiven(ExperienceId);
}

void ATulGameModeBase::OnMatchAssignmentGiven(FPrimaryAssetId ExperienceId)
{
	// 해당 함수는 ExperienceManagerComponent를 활용하여 Experience를 로딩하기 위해, ExperienceManagerCompoenent의 ServerSetCurrentExperience를 호출한다

	check(ExperienceId.IsValid());

	UTulExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UTulExperienceManagerComponent>();
	check(ExperienceManagerComponent);
	ExperienceManagerComponent->ServerSetCurrentExperience(ExperienceId);
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
	// PlayerController를 순회하며
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		APlayerController* PC = Cast<APlayerController>(*Iterator);

		// PlayerController가 Pawn을 Possess하지 않았다면, RestartPlayer를 통해 Pawn을 다시 Spawn한다
		// - 한번 OnPossess를 보도록 하자
		if (PC && PC->GetPawn() == nullptr)
		{
			if (PlayerCanRestart(PC))
			{
				RestartPlayer(PC);
			}
		}
	}
}

const UTulPawnData* ATulGameModeBase::GetPawnDataForController(const AController* InController) const
{
	// 게임 도중에 PawnData가 오버라이드 되었을 경우, PawnData는 PlayerState에서 가져오게 됨
	if (InController)
	{
		if (const ATulPlayerState* TulPS = InController->GetPlayerState<ATulPlayerState>())
		{
			// GetPawnData 구현
			if (const UTulPawnData* PawnData = TulPS->GetPawnData<UTulPawnData>())
			{
				return PawnData;
			}
		}
	}

	// fall back to the default for the current experience
	// 아직 PlayerState에 PawnData가 설정되어있지 않은 경우, ExperienceManagerComponent의 CurrentExperience에서 가져와서 설정
	check(GameState);
	UTulExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UTulExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	if (ExperienceManagerComponent->IsExperienceLoaded())
	{
		// GetExperienceChecked 구현
		const UTulExperienceDefinition* Experience = ExperienceManagerComponent->GetCurrentExperienceChecked();
		if (Experience->DefaultPawnData)
		{
			return Experience->DefaultPawnData;
		}
	}

	// 어떠한 케이스에도 핸들링 안되었으면 nullptr
	return nullptr;
}
