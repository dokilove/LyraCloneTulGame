// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulGame/Equipment/TulGameplayAbility_FromEquipment.h"
#include "TulGameplayAbility_RangedWeapon.generated.h"

class UTulRangedWeaponInstance;

/** 어디 대상으로 Target으로 설정할지 옵션들 (Lyra의 경우, 다양한 옵션 존재) */
UENUM(BlueprintType)
enum class ETulAbilityTargetingSource : uint8
{
	/** Camera 기준으로 진행 */
	CameraTowardsFocus,
};

/**
 * 
 */
UCLASS()
class TULGAME_API UTulGameplayAbility_RangedWeapon : public UTulGameplayAbility_FromEquipment
{
	GENERATED_BODY()
	
public:
	struct FRangedWeaponFiringInput
	{
		FVector StartTrace;
		FVector EndAim;
		FVector AimDir;
		UTulRangedWeaponInstance* WeaponData = nullptr;
		bool bCanPlayBulletFX = false;

		FRangedWeaponFiringInput()
			: StartTrace(ForceInitToZero)
			, EndAim(ForceInitToZero)
			, AimDir(ForceInitToZero)
		{}
	};

	UTulGameplayAbility_RangedWeapon(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	void StartRangedWeaponTargeting();

	void PerformLocalTargeting(TArray<FHitResult>& OutHits);
	FTransform GetTargetingTransform(APawn* SourcePawn, ETulAbilityTargetingSource Source);
	FVector GetWeaponTargetingSourceLocation() const;
	void TraceBulletsInCartridge(const FRangedWeaponFiringInput& InputData, TArray<FHitResult>& OutHits);
	FHitResult DoSingleBulletTrace(const FVector& StartTrace, const FVector& EndTrace, float SweepRadius, bool bIsSimulated, TArray<FHitResult>& OutHits) const;
	FHitResult WeaponTrace(const FVector& StartTrace, const FVector& EndTrace, float SweepRadius, bool bIsSimulated, TArray<FHitResult>& OutHitResults) const;
	void AddAdditionalTraceIgnoreActors(FCollisionQueryParams& TraceParams) const;
	ECollisionChannel DetermineTraceChannel(FCollisionQueryParams& TraceParams, bool bIsSimulated) const;
	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag);
	/** called when target data is ready */
	UFUNCTION(BlueprintImplementableEvent)
	void OnRangeWeaponTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);

	UTulRangedWeaponInstance* GetWeaponInstance();
};
