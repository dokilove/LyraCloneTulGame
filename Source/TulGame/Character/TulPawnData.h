// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TulPawnData.generated.h"

class UTulAbilitySet;
class UTulInputConfig;
class UTulCameraMode;

/**
 * 
 */
UCLASS()
class TULGAME_API UTulPawnData : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UTulPawnData(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	/** Pawn의 Class*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tul|Pawn")
	TSubclassOf<APawn> PawnClass;

	/** Camera Mode */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tul|Camera")
	TSubclassOf<UTulCameraMode> DefaultCameraMode;

	/** input configuration used by player controlled pawns to create input mappings and bind input actions */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "TUL|InputConfig")
	TObjectPtr<UTulInputConfig> InputConfig;

	/**  해당  Pawn의 Ability System에 허용할 AbilitySet */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tul|Abilities")
	TArray<TObjectPtr<UTulAbilitySet>> AbilitySets;
};
