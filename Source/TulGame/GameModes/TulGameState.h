// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TulGameState.generated.h"

class UTulExperienceManagerComponent;

/**
 * 
 */
UCLASS()
class TULGAME_API ATulGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	ATulGameState();

public:
	UPROPERTY()
	TObjectPtr<UTulExperienceManagerComponent> ExperienceManagerComponent;
};
