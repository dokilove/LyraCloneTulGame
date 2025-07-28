// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TulGameModeBase.generated.h"

class UTulExperienceDefinition;

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
	virtual void InitGameState() final;

	/** HandleStartingNewPlayer */
	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) final;

	/** SpawnDefaultPawnAtTransform */
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation(AController* NewPlayer, const FTransform& SpawnTransform) final;

	/**
	* member methods
	*/
	void HandleMatchAssignmentIfNotExpectingOne();
	bool IsExperienceLoaded() const;
	void OnExperienceLoaded(const UTulExperienceDefinition* CurrentExperience);
};
