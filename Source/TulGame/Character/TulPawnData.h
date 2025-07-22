// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TulPawnData.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UTulPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
