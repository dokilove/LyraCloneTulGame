// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CommonUserWidget.h"
#include "UObject/ObjectPtr.h"
#include "UObject/UObjectGlobals.h"
#include "TulWeaponUserInterface.generated.h"

/** forward declaration */
class UTulWeaponInstance;

/**
 * 
 */
UCLASS()
class TULGAME_API UTulWeaponUserInterface : public UCommonUserWidget
{
	GENERATED_BODY()
public:
	UTulWeaponUserInterface(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Weapon 변경에 따른 BP Event */
	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponChanged(UTulWeaponInstance* OldWeapon, UTulWeaponInstance* NewWeapon);

	/**
	* UUserWidget's interface
	*/
	virtual void NativeTick(const FGeometry& MyGeoMetry, float InDeltaTime) override;

	/** 현재 장착된 WeaponInstance를 추적한다 (NativeTick을 활용하여 주기적 업데이트한다) */
	UPROPERTY(Transient)
	TObjectPtr<UTulWeaponInstance> CurrentInstance;
};
