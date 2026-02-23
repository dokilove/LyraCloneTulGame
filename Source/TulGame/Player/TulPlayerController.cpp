// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPlayerController.h"
#include "TulPlayerState.h"
#include "TulGame/AbilitySystem/TulAbilitySystemComponent.h"
#include "TulGame/Camera/TulPlayerCameraManager.h"

ATulPlayerController::ATulPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ATulPlayerCameraManager::StaticClass();
}

void ATulPlayerController::PostProcessInput(const float DeltaTime, const bool bGamePaused)
{
	// 우선 PostProcessInput()가 언제 호출되는지 확인해보자:
	// - UPlayerInput::ProcessInputStack()에서 호출된다

	if (UTulAbilitySystemComponent* TulASC = GetTulAbilitySystemComponent())
	{
		TulASC->PrecessAbilityInput(DeltaTime, bGamePaused);
	}

	Super::PostProcessInput(DeltaTime, bGamePaused);
}

ATulPlayerState* ATulPlayerController::GetTulPlayerState() const
{
	// ECastCheckedType의 NullAllowed는 Null반환을 의도할 경우 유용하다
	return CastChecked<ATulPlayerState>(PlayerState, ECastCheckedType::NullAllowed);
}

UTulAbilitySystemComponent* ATulPlayerController::GetTulAbilitySystemComponent() const
{
	const ATulPlayerState* TulPS = GetTulPlayerState();
	return (TulPS ? TulPS->GetTulAbilitySystemComponent() : nullptr);
}
