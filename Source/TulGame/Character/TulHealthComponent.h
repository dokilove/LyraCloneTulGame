// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkComponent.h"
#include "Delegates/Delegate.h"
#include "TulHealthComponent.generated.h"

/** forward declarations */
class UTulAbilitySystemComponent;
class UTulHealthSet;
class UTulHealthComponent;
class AActor;
struct FOnAttributeChangeData;

/** Health 변화 콜백을 위한 델리게이트*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FTulHealth_AttributeChanged, UTulHealthComponent*, HealthComponent, float, OldValue, float, NewValue, AActor*, Instigator);

/**
 * 
 */
UCLASS()
class TULGAME_API UTulHealthComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()
public:
	UTulHealthComponent(const FObjectInitializer& ObjectInitializer);

	/** Actor (보통 ACharacter/APawn)의 HealthComponent를 반환 */
	UFUNCTION(BlueprintPure, Category = "Tul|Health")
	static UTulHealthComponent* FindHealthComponent(const AActor* Actor);

	/** 아래의 UFUNCTION은 HealthSet의 Attribute에 접근하기 위한 BP Accessor 함수들 */
	UFUNCTION(BlueprintCallable, Category = "Tul|Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Tul|Health")
	float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Tul|Health")
	float GetHealthNormalized() const;

	/** ASC와 HealthSet 초기화 */
	void InitializeWithAbilitySystem(UTulAbilitySystemComponent* InASC);
	void UninitializeWithAbilitySystem();

	/** ASC를 통해, HealthSet의 HealthAttribute 변경이 있을 때 호출하는 메서드 (내부적으로는 OnHealthChanged 호출) */
	void HandleHealthChanged(const FOnAttributeChangeData& ChangeData);
	 
	/** HealthSet을 접근하기 위한 AbilitySystemComponent */
	UPROPERTY()
	TObjectPtr<UTulAbilitySystemComponent> AbilitySystemComponent;

	/** 캐싱된 HealthSet 레퍼런스 */
	UPROPERTY()
	TObjectPtr<const UTulHealthSet> HealthSet;

	/** health 변화에 따른 Delegate(Multicast) */
	UPROPERTY(BlueprintAssignable)
	FTulHealth_AttributeChanged OnHealthChanged;
};
