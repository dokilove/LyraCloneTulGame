// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TulGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UTulGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
