#pragma once

#include "Abilities/GameplayAbilityTargetTypes.h"
#include "TulGameplayAbilityTargetData_SingleTarget.generated.h"

USTRUCT()
struct FTulGameplayAbilityTargetData_SingleTargetHit : public FGameplayAbilityTargetData_SingleTargetHit
{
	GENERATED_BODY()
public:
	FTulGameplayAbilityTargetData_SingleTargetHit() : CartridgeID(-1)
	{ }

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return FTulGameplayAbilityTargetData_SingleTargetHit::StaticStruct();
	}

	/** 탄약 ID (카트리지) */
	UPROPERTY()
	int32 CartridgeID;
};