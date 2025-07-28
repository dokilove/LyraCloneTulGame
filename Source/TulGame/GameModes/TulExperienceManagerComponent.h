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
 * - �� �״��, �ش� component�� game state�� owner�� �����鼭, experience�� ���� ������ ������ �ִ� component�̴�
 * - �Ӹ� �ƴ϶�, manager��� �ܾ ���ԵǾ� �ֵ���, experience �ε� ���� ������Ʈ �� �̺�Ʈ�� �����Ѵ�
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

	/** Experience�� �ε� ���¸� ����͸� */
	ETulExperienceLoadState LoadState = ETulExperienceLoadState::Unloaded;

	/** Experience �ε��� �Ϸ�� ����, Broadcasting Delegate */
	FOnTulExperienceLoaded OnExperienceLoaded;
};
