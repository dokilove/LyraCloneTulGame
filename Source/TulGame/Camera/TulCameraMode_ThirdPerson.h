// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulCameraMode.h"
#include "TulCameraMode_ThirdPerson.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TULGAME_API UTulCameraMode_ThirdPerson : public UTulCameraMode
{
	GENERATED_BODY()
	
public:
	UTulCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
