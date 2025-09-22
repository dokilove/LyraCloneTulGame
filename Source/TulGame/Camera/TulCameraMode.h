// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulCameraMode.generated.h"

class UTulCameraComponent;

/**
* FTulCameraModeView
*/
struct FTulCameraModeView
{
	FTulCameraModeView();

	void Blend(const FTulCameraModeView& Other, float OtherWeight);

	FVector Location;
	FRotator Rotation;
	FRotator ControlRotation;
	float FieldOfView;
};

/**
*  [0, 1]을 BlendFuction 에 맞게 재매핑을 위한 타입
*/
UENUM(BlueprintType)
enum class ETulCameraModelBlendFunction : uint8
{
	Linear,
	/**
	* Ease In/Out은 exponent 값에 의해 조절된다:
	*/
	EaseIn,
	EaseOut,
	EaseInOut,
	COUNT
};

/** Camera Blending 대상 유닛 */
UCLASS(Abstract, NotBlueprintable)
class UTulCameraMode : public UObject
{
	GENERATED_BODY()
	
public:
	UTulCameraMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* member methods
	*/
	void UpdateCameraMode(float DeltaTime);
	virtual void UpdateView(float DeltaTime);
	void UpdateBlending(float DeltaTime);

	UTulCameraComponent* GetTulCameraComponent() const;
	AActor* GetTargetActor() const;
	FVector GetPivotLocation() const;
	FRotator GetPivotRotation() const;

	/**
	* member variables
	*/
	/** CameraMode에 의해 생성된 CameraModeView */
	FTulCameraModeView View;

	/** Camera Mode의 FOV */
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "5.0", UIMax = "170", ClampMin = "5.0", ClampMax = "170.0"))
	float FieldOfView;

	/** Camera Mode의 Pitch [Min, Max] */
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMin;

	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMax;

	/** 얼마동안 Blend를 진행할 지 시간을 의미 */
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendTime;
	
	/** 선형적인 Blend 값 [0, 1] */
	float BlendAlpha;

	/** 
	* 해당 CameraMode의 최종 Blend 값
	* 앞서 BlendAlpha의 선형 값을 매핑하여 최종 BlendWeight를 계산 (코드를 보며, 이해해보자)
	*/
	float BlendWeight;

	/** 
	* EaseIn/Out에 사용한 Exponent
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendExponent;

	/** Blend function */
	ETulCameraModelBlendFunction BlendFunction;
};

/** Camera Blending 을 담당a하는 객체 */
UCLASS()
class UTulCameraModeStack : public UObject
{
	GENERATED_BODY()

public:
	UTulCameraModeStack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* member methods
	*/
	UTulCameraMode* GetCameraModeInstance(TSubclassOf<UTulCameraMode>& CameraModeClass);
	void PushCameraMode(TSubclassOf<UTulCameraMode>& CameraModeClass);
	void EvaluateStack(float DeltaTime, FTulCameraModeView& OutCameraModeView);
	void UpdateStack(float DeltaTime);
	void BlendStack(FTulCameraModeView& OutCameraModeView);
	/**
	* member variables
	*/


	/** 생성된 CameraMode를 관리 */
	UPROPERTY()
	TArray<TObjectPtr<UTulCameraMode>> CameraModeInstances;

	/** Camera Matrix Blend 업데이트 진행 큐 */
	UPROPERTY()
	TArray<TObjectPtr<UTulCameraMode>> CameraModeStack;
};
