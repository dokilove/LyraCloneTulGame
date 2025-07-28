// Fill out your copyright notice in the Description page of Project Settings.


#include "TulGameModeBase.h"
#include "TulGameState.h"
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
	GetWorld()->GetTimerManager().SetTimerForNextTick(this, &ThisClass::HandleMatchAssignmentIfNotExpetingOne);
}

void ATulGameModeBase::HandleMatchAssignmentIfNotExpetingOne()
{

}
