// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameStateComponent.h"
#include "TulExperienceManagerComponent.generated.h"

class UTulExperienceDefinition;

enum class ETulExperienceLoadState
{
	Unloaded,
	Loading,
	Loaded,
	Deactivating,
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnTulExperienceLoaded, const UTulExperienceDefinition*);

/**
 * TulExperienceManagerComponent
 * - 말 그대로, 해당 component는 game state를 owner로 가지면서, experience의 상태 정보를 가지고 있는 component이다
 * - 뿐만 아니라, manager라는 단어가 포함되어 있듯이, experience 로딩 상태 업데이트 및 이벤트를 관리한다
 */
UCLASS()
class TULGAME_API UTulExperienceManagerComponent : public UGameStateComponent
{
	GENERATED_BODY()
public:
	/**
	* member methods
	*/
	bool IsExperienceLoaded() { return (LoadState == ETulExperienceLoadState::Loaded) && (CurrentExperience != nullptr); }
	
public:
	UPROPERTY()
	TObjectPtr<const UTulExperienceDefinition> CurrentExperience;

	/** Experience의 로딩 상태를 모니터링 */
	ETulExperienceLoadState LoadState = ETulExperienceLoadState::Unloaded;

	/** Experience 로딩이 완료된 이후, Broadcasting Delegate */
	FOnTulExperienceLoaded OnExperienceLoaded;
};
