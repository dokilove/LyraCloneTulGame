// Fill out your copyright notice in the Description page of Project Settings.


#include "TulInputConfig.h"
#include "TulGame/TulLogChannels.h"

UTulInputConfig::UTulInputConfig(const FObjectInitializer& ObjectIniitalizer) : Super(ObjectIniitalizer)
{
}

const UInputAction* UTulInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	// NativeInputAction을 순회하며, Input으로 들어온 InputTag가 있는지 체크한다
	// - 있으면 그에 따른 InputAction을 반환하지만 없다면 그냥 nullptr을 반환한다
	for (const FTulInputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}
	
	if (bLogNotFound)
	{
		UE_LOG(LogTul, Error, TEXT("can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* UTulInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FTulInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTul, Error, TEXT("can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
