// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "TulGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class ETulAbilityActivationPolicy : uint8
{
	/** Input이 Trigger 되었을 경우 (Pressed/Released) */
	OnInputTriggered,
	/** Input이 Held되어 있을 경우 */
	WhileInputActive,
	/** Avatar가 생성되었을 경우, 바로 할당 */
	OnSpawn,
};

/** forward declarations */
class UTulAbilityCost;

/**
 * 
 */
UCLASS()
class TULGAME_API UTulGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UTulGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* UGameplayAbility interface
	*/
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;

	/**  언제 GA가 활성화될지 정책 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tul|AbilityActivation")
	ETulAbilityActivationPolicy ActivationPolicy;

	/** ability costs to apply TulGameplayAbility separately */
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Tul|Costs")
	TArray<TObjectPtr<UTulAbilityCost>> AdditionalCosts;
};
