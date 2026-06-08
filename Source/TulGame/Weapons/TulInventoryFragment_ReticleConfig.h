// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "Templates/SubclassOf.h"
#include "TulGame/Inventory/TulInventoryItemDefinition.h"
#include "TulInventoryFragment_ReticleConfig.generated.h"

/** forward declaration */
class UTulReticleWidgetBase;

UCLASS()
class UTulInventoryFragment_ReticleConfig : public UTulInventoryItemFragment
{
	GENERATED_BODY()
public:
	/** 무기에 결합된 Reticle Widget 정보를 가지고 있는 Fragment */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Reticle)
	TArray<TSubclassOf<UTulReticleWidgetBase>> ReticleWidgets;
	
};
