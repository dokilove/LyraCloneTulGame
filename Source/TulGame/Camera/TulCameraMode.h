// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulCameraMode.generated.h"

/** Camera Blending 대상 유닛 */
UCLASS()
class TULGAME_API UTulCameraMode : public UObject
{
	GENERATED_BODY()
	
public:
	UTulCameraMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};

/** Camera Blending 을 담당하는 객체 */
UCLASS()
class UTulCameraModeStack : public UObject
{
	GENERATED_BODY()

public:
	UTulCameraModeStack(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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
