// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPlayerCameraManager.h"

ATulPlayerCameraManager::ATulPlayerCameraManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	DefaultFOV = TUL_CAMERA_DEFAULT_FOV;
	ViewPitchMin = TUL_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = TUL_CAMERA_DEFAULT_PITCH_MAX;
}
