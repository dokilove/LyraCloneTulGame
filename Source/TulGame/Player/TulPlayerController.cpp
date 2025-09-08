// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPlayerController.h"
#include "TulGame/Camera/TulPlayerCameraManager.h"

ATulPlayerController::ATulPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PlayerCameraManagerClass = ATulPlayerCameraManager::StaticClass();
}
