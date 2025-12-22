// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TulInventoryItemInstance.generated.h"

class UTulInventoryItemDefinition;
/**
 * 
 */
UCLASS()
class TULGAME_API UTulInventoryItemInstance : public UObject
{
	GENERATED_BODY()
	
public:
	UTulInventoryItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Inventory Item의 인스턴스에는 무엇으로 정의되었는지 메타 클래스인 TulInventoryItemDefinition을 들고 있다*/
	UPROPERTY()
	TSubclassOf<UTulInventoryItemDefinition> ItemDef;
};
