// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TulPlayerState.generated.h"

class UTulAbilitySystemComponent;
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
	ATulPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
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
	UTulAbilitySystemComponent* GetTulAbilitySystemComponent() const { return AbilitySystemComponent;  }
	UPROPERTY()
	TObjectPtr<const UTulPawnData> PawnData;
	
	UPROPERTY(VisibleAnywhere, Category =  "Tul|PlayerState")
	TObjectPtr<UTulAbilitySystemComponent> AbilitySystemComponent;
};
