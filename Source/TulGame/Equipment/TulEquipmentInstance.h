// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TulEquipmentInstance.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class TULGAME_API UTulEquipmentInstance : public UObject
{
	GENERATED_BODY()

public:
	UTulEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** 어떤 InventotyItemInstance에 의해 활성화되었는지 (추후, QuickBarComponent에서 보게 될 것이다) */
	UPROPERTY()
	TObjectPtr<UObject> Instigator;

	/** TulEquipmentDefinition에 맞게 Spawn된 Actor Instance들 */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;
	
};
