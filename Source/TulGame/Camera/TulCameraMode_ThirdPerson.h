// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulCameraMode.h"
#include "TulCameraMode_ThirdPerson.generated.h"

class UCurveVector;

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TULGAME_API UTulCameraMode_ThirdPerson : public UTulCameraMode
{
	GENERATED_BODY()
	
public:
	UTulCameraMode_ThirdPerson(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* UTulCameraMode's interface
	*/
	virtual void UpdateView(float DeltaTime) override;

	/**
	* member variables
	*/
	UPROPERTY(EditDefaultsOnly, Category = "Third Person")
	TObjectPtr<const UCurveVector> TargetOffsetCurve;
};
