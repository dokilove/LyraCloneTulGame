// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TulInventoryItemDefinition.h"
#include "Templates/SubclassOf.h"
#include "TulInventoryFragment_EquippableItem.generated.h"

class UTulEquipmentDefinition;

/**
 * 
 */
UCLASS()
class TULGAME_API UTulInventoryFragment_EquippableItem : public UTulInventoryItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = Tul)
	TSubclassOf<UTulEquipmentDefinition> EquipmentDefinition;
};
