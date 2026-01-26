// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TulEquipmentInstance.generated.h"

/**
 * 
 */

struct FTulEquipmentActorToSpawn;

UCLASS(BlueprintType, Blueprintable)
class TULGAME_API UTulEquipmentInstance : public UObject
{
	GENERATED_BODY()

public:
	UTulEquipmentInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* Blueprint 정의를 위한 Equip/Unequip 함수
	*/
	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnEquipped"))
	void K2_OnEquipped();

	UFUNCTION(BlueprintImplementableEvent, Category = Equipment, meta = (DisplayName = "OnUnequipped"))
	void K2_OnUnequipped();

	UFUNCTION(BlueprintPure, Category = Equipment)
	APawn* GetPawn() const;

	void SpawnEquipmentActors(const TArray<FTulEquipmentActorToSpawn>& ActorsToSpawn);
	void DestroyEquipmentActors();

	/**
	* interfaces
	*/
	virtual void OnEquipped();
	virtual void OnUnequipped();

	/** 어떤 InventotyItemInstance에 의해 활성화되었는지 (추후, QuickBarComponent에서 보게 될 것이다) */
	UPROPERTY()
	TObjectPtr<UObject> Instigator;

	/** TulEquipmentDefinition에 맞게 Spawn된 Actor Instance들 */
	UPROPERTY()
	TArray<TObjectPtr<AActor>> SpawnedActors;
	
};
