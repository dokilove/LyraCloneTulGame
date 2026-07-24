// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonUserWidget.h"
#include "UObject/ObjectPtr.h"
#include "UObject/UObjectGlobals.h"
#include "TulReticleWidgetBase.generated.h"

/** forward declarations */
class UTulWeaponInstance;
class UTulInventoryItemInstance;

UCLASS()
class UTulReticleWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UTulReticleWidgetBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	void InitializeFromWeapon(UTulWeaponInstance* InWeapon);

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponInitialized();

	/**
	* WeaponInstance/InventoryInstance를 상태 추적용으로 캐싱 목적
	*/
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTulWeaponInstance> WeaponInstance;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTulInventoryItemInstance> InventoryInstance;
};
