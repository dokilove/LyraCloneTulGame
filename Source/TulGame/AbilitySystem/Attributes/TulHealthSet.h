// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TulHealthSet.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulHealthSet : public UTulAttributeSet
{
	GENERATED_BODY()
public:
	UTulHealthSet();

	/**
	* 앞서 TulAttributeSet에서 정의했던, ATTRIBUTE_ACCESSORS를 통해, 아래 정의한 멤버변수와 똑같이 이름을 설정한다
	* - ATTRIBUTE_ACCESSORS의 Macro의 정의부분을 한번 살펴보자
	*/
	ATTRIBUTE_ACCESSORS(UTulHealthSet, Health);
	ATTRIBUTE_ACCESSORS(UTulHealthSet, MaxHealth);
	ATTRIBUTE_ACCESSORS(UTulHealthSet, Healing);

	/** 현재 체력 */
	UPROPERTY(BlueprintReadOnly, Category = "Tul | Health")
	FGameplayAttributeData Health;

	/** 체력 최대치 */
	UPROPERTY(BlueprintReadOnly, Category = "Tul | Health")
	FGameplayAttributeData MaxHealth;

	/** 체력 회복치 */
	UPROPERTY(BlueprintReadOnly, Category = "Tul | Health")
	FGameplayAttributeData Healing;
};
