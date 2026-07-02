// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TulAttributeSet.h"
#include "TulCombatSet.generated.h"

/**
 * CombatSet은 이름 그대로, 전투와 관련된 Attribute를 담고 있는 Set이다
 * - 현재는 BaseHeal만 있지만, BaseDamage도 추가하여, 완전한 CombatSet에 필요한 AttributeSet을 정의 가능하다
 */
UCLASS()
class TULGAME_API UTulCombatSet : public UTulAttributeSet
{
	GENERATED_BODY()
public:
	UTulCombatSet();

	ATTRIBUTE_ACCESSORS(UTulCombatSet, BaseHeal);

	/**
	* FGameplayAttribute가 참고하는 실제 AttributeSet에 있는 데이터이다 (float보다 해당 struct를 사용하는 것을 추천)
	* - Healing의 단위를 의미한다
	* - e.g. 5.0f라면, Period당 5씩 Healing된다는 의미
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Tul | Combat")
	FGameplayAttributeData BaseHeal;
};
