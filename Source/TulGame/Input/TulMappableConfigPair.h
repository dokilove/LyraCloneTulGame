// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TulMappableConfigPair.generated.h"

/** forward declaration */
class UPlayerMappableInputConfig;

USTRUCT()
struct FTulMappableConfigPair
{
	GENERATED_BODY()
public:
	FTulMappableConfigPair() = default;

	UPROPERTY(EditAnywhere)
	TSoftObjectPtr<UPlayerMappableInputConfig> Config;

	UPROPERTY(EditAnywhere)
	bool bShouldActivateAutomatically = true;
};