// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TulInventoryManagerComponent.generated.h"

/** forward declarations */
class UTulInventoryItemInstance;
class UTulInventoryItemDefinition;

/** Inventory Item 단위 객체 */
USTRUCT(BlueprintType)
struct FTulInventoryEntry
{
	GENERATED_BODY()

	UPROPERTY()
	TObjectPtr<UTulInventoryItemInstance> Instance = nullptr;
};

/** Inventory Item 관리 객체 */
USTRUCT(BlueprintType)
struct FTulInventoryList
{
	GENERATED_BODY()

	FTulInventoryList(UActorComponent* InOwnerComponent = nullptr) : OwnerComponent(InOwnerComponent)
	{}

	UPROPERTY()
	TArray<FTulInventoryEntry> Entries;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};

/**
* PlayerController의 Component로서 Inventory를 관리한다
* - 사실 UActorComponent 상속이 아닌 UControllerComponent를 상속받아도 될거 같은데 일단 Lyra기준으로 UActorComponent를 상속받는다
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TULGAME_API UTulInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UTulInventoryManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	FTulInventoryList InventoryList;

		
};
