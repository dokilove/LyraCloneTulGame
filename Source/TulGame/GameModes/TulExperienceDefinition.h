// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TulExperienceDefinition.generated.h"

class UTulPawnData;

/**
 * 
 */
UCLASS()
class TULGAME_API UTulExperienceDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UTulExperienceDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* member variables
	*/
	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TObjectPtr<UTulPawnData> DefaultPawnData;

	/**
	* �ش� property�� �ܼ��� ��ŷ �� �������� ���ܵд�
	* - ���� ��忡 ���� GameFeature plugin�� �ε��ϴµ� �̿� ���� �������� �����ϸ� �ȴ�
	* - ���� ShooterCore ���� Plugin �۾��� ���, �����ϰ� �� �����̴�
	*/
	UPROPERTY(EditDefaultsOnly, Category=Gameplay)
	TArray<FString> GameFeaturesToEnable;
};
