// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TulGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API ATulGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATulGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/**
	* member methods
	*/
	void HandleMatchAssignmentIfNotExpetingOne();
};
