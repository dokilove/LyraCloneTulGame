// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameUIManagerSubsystem.generated.h"

class UGameUIPolicy;
class UCommonLocalPlayer;

/**
 * 
 */
UCLASS(Abstract, config = Game)
class COMMONGAME_API UGameUIManagerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UGameUIManagerSubsystem();

	void SwitchToPolicy(UGameUIPolicy* InPolicy);

	/**
	* UGameInstanceSubsystem's interface
	*/
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	/**
	* UGameUIManagerSubsystem's interface
	*/
	virtual void NotifyPlayerAdded(UCommonLocalPlayer* LocalPlayer);
	virtual void NotifyPlayerRemoved(UCommonLocalPlayer* LocalPlayer);
	virtual void NotifyPlayerDestroyed(UCommonLocalPlayer* LocalPlayer);

	UPROPERTY(Transient)
	TObjectPtr<UGameUIPolicy> CurrentPolicy = nullptr;

	/**
	* default UI policy를 생성할 class
	* - 우리는 해당 클래스는 B_BttGameUIPolicy로 지정할 것이다
	*/
	UPROPERTY(Config, EditAnywhere)
	TSoftClassPtr<UGameUIPolicy> DefaultUIPolicyClass;
};
