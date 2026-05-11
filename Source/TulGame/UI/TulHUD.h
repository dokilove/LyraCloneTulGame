// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/HUD.h"
#include "TulHUD.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API ATulHUD : public AHUD
{
	GENERATED_BODY()
public:
	ATulHUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* GameFrameworkComponentManager의 AddReceiver를 위한 메서드들
	*/
	virtual void PreInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};
