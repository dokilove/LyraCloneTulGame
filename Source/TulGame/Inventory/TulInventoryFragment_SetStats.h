// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "TulInventoryItemDefinition.h"
#include "TulInventoryFragment_SetStats.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulInventoryFragment_SetStats : public UTulInventoryItemFragment
{
	GENERATED_BODY()
public:
	virtual void OnInstanceCreated(UTulInventoryItemInstance* Instance) const override;

	/** InitialItemStats gives constructor's parameters for TulGameplayTagStackContainer */
	UPROPERTY(EditDefaultsOnly, Category = Equipment)
	TMap<FGameplayTag, int32> InitialItemStats;
};
