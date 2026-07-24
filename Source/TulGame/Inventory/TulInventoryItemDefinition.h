// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TulInventoryItemDefinition.generated.h"

class UTulInventoryItemInstance;

/**
* Inventory에 대한 Fragment는 확 와닫지 않을 수 있다:
* - Lyra에서 사용하는 예시를 통해 이해해보자:
*	- ULyraInventoryFragment EquippableItem은 EquipmentItemDefinition을 가지고 있으며, 장착 가능한 아이템을 의미한다
*	- ULyraInventoryFragment SetStats는 아이템에 대한 정보를 가지고 있다
*		-	Rifle에 대한 SetStats로 총알(Ammo)에 대한 장착 최대치와 현재 남은 잔탄 수를 예시로 들 수 있다
*	- 등등...
*/
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class UTulInventoryItemFragment : public UObject
{
	GENERATED_BODY()
public:
	/** interface to call when inventory item instance is added to UTulInventoryManagerComponent's InventoryList */
	virtual void OnInstanceCreated(UTulInventoryItemInstance* Instance) const {}
};

/**
 * 
 */
UCLASS(Blueprintable)
class TULGAME_API UTulInventoryItemDefinition : public UObject
{
	GENERATED_BODY()
public:
	UTulInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const UTulInventoryItemFragment* FindFragmentByClass(TSubclassOf<UTulInventoryItemFragment> FragmentClass) const;

	/** Inventory Item 정의(메타) 이름 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FText DisplayName;

	/** Inventory Item의 Component를 Fragment로 인식하면 된다 */
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Display)
	TArray<TObjectPtr<UTulInventoryItemFragment>> Fragments;
};
