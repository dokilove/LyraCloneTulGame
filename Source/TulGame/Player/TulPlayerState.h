// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TulPlayerState.generated.h"

class UTulPawnData;
class UTulExperienceDefinition;
/**
 * 
 */
UCLASS()
class TULGAME_API ATulPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/**
	* AActor's interface
	*/
	virtual void PostInitializeComponents() final;

	/**
	* member methods
	*/
	template <class T>
	const T* GetPawnData() const { return Cast<T>(PawnData); }
	void OnExperienceLoaded(const UTulExperienceDefinition* CurrentExperience);
	void SetPawnData(const UTulPawnData* InPawnData);

	UPROPERTY()
	TObjectPtr<const UTulPawnData> PawnData;
	
};
