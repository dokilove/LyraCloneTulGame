// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TulExperienceActionSet.generated.h"

class UGameFeatureAction;

/**
 * 
 */
UCLASS()
class TULGAME_API UTulExperienceActionSet : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UTulExperienceActionSet();

	/**
	* member variables
	*/
	UPROPERTY(EditAnywhere, Category = "Actions to Perform")
	TArray<TObjectPtr<UGameFeatureAction>> Actions;
};
