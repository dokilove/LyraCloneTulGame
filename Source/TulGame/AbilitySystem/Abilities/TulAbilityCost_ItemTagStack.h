// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulAbilityCost.h"
#include "TulAbilityCost_ItemTagStack.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Item Tag Stack"))
class TULGAME_API UTulAbilityCost_ItemTagStack : public UTulAbilityCost
{
	GENERATED_BODY()
public:
	UTulAbilityCost_ItemTagStack();

	virtual bool CheckCost(const UTulGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, FGameplayTagContainer* OptionalRelevantTags) const override;
	virtual void ApplyCost(const UTulGameplayAbility* Ability, const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;

	/**
	* how much of the tag spend:
	* - FScalableFloat is scaled by Curve with base float value
	* - Curve us normally indexed by ability level
	*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Costs)
	FScalableFloat Quantity;

	/** gameplay tag combined with the cost */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Costs)
	FGameplayTag Tag;

	/** failure identifier with gameplay-tag */
	UPROPERTY(EditAnywhere, BLueprintReadOnly, Category = Costs)
	FGameplayTag FailureTag;
};
