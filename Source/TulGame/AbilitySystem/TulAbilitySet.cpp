// Fill out your copyright notice in the Description page of Project Settings.


#include "TulAbilitySet.h"
#include "TulAbilitySystemComponent.h"
#include "Abilities/TulGameplayAbility.h"

void FTulAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FTulAbilitySet_GrantedHandles::TakeFromAbilitySystem(UTulAbilitySystemComponent* TulASC)
{
}

UTulAbilitySet::UTulAbilitySet(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTulAbilitySet::GiveToAbilitySystem(UTulAbilitySystemComponent* TulASC, FTulAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject)
{
	check(TulASC);

	if (!TulASC->IsOwnerActorAuthoritative())
	{
		return;
	}

	// gameplay abilities를 허용:
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FTulAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];
		if (!IsValid(AbilityToGrant.Ability))
		{
			continue;
		}

		// GiveAbility()에서 만약 EGameplayAbilityInstancingPolicy::InstancedPerActor라면, 내부적으로 Instance를 생성하지만 그렇지 않으면 CDO를 할당한다
		// - 이를 통해 UObject 갯수를 줄여 UObject가 늘어남에 따라 늘어나는 성능적/메모리적 부하를 줄일 수 있다.
		UTulGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UTulGameplayAbility>();

		// AbilitySpec은 GiveAbility로 전달되러, ActivatableAbilities에 추가된다
		FGameplayAbilitySpec AbilitySpec(AbilityCDO, AbilityToGrant.AbilityLevel);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

		// GiveAbility()를 잠깐 살펴보도록 하자:
		const FGameplayAbilitySpecHandle AbilitySpecHandle = TulASC->GiveAbility(AbilitySpec);
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}
}
