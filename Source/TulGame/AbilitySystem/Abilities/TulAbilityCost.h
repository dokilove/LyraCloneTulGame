// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulGameplayAbility.h"
#include "UObject/NoExportTypes.h"
#include "TulAbilityCost.generated.h"

/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class TULGAME_API UTulAbilityCost : public UObject
{
	GENERATED_BODY()
public:
	UTulAbilityCost();

	/**
	* CheckCost and ApplyCost function signature from UGameAbility's CheckCost and ApplyCost
	* - You can think TulAbilityCost as managable-unit to check/apply cost for GameplayAbility
	*/
	virtual bool CheckCost(const UTulGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const
	{
		return true;
	}
	
	virtual void ApplyCost(const UTulGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
	{

	}
};
