// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulGame/Cosmetics/TulCosmeticAnimationTypes.h"
#include "TulGame/Equipment/TulEquipmentInstance.h"
#include "TulWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulWeaponInstance : public UTulEquipmentInstance
{
	GENERATED_BODY()
	
public:
	UTulWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Weapon에 Equip/Unequip에 대한 Animation Set 정보를 들고있다 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FTulAnimLayerSelectionSet EquippedAnimSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	FTulAnimLayerSelectionSet UnequippedAnimSet;
};
