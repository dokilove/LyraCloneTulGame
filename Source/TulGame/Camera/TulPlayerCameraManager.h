// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "TulPlayerCameraManager.generated.h"

/**
* Controller에 바인딩된 CameraManager
*/
#define TUL_CAMERA_DEFAULT_FOV (80.0f)
#define TUL_CAMERA_DEFAULT_PITCH_MIN (-89.0f)
#define TUL_CAMERA_DEFAULT_PITCH_MAX (89.0f)
/**
 * 
 */
UCLASS()
class TULGAME_API ATulPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	ATulPlayerCameraManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
};
