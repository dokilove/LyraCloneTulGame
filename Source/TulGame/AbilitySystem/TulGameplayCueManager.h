// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayCueManager.h"
#include "TulGameplayCueManager.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulGameplayCueManager : public UGameplayCueManager
{
	GENERATED_BODY()
public:
	static UTulGameplayCueManager* Get();

	UTulGameplayCueManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	void RefreshGameplayCuePrimaryAsset();
};
