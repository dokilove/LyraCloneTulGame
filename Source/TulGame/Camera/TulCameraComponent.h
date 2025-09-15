// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulCameraMode.h"
#include "Camera/CameraComponent.h"
#include "TulCameraComponent.generated.h"

class UTulCameraModeStack;

/** template forward declaration */
template <class TClass> class TSubclassof;

/** (return type, delegate_name) */
DECLARE_DELEGATE_RetVal(TSubclassOf<UTulCameraMode>, FTulCameraModeDelegate);

UCLASS()
class TULGAME_API UTulCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
public:
	UTulCameraComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	static UTulCameraComponent* FindCameraComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UTulCameraComponent>() : nullptr); }

	/**
	* member methods
	*/
	AActor* GetTargetActor() const { return GetOwner(); }
	void UpdateCameraModes();

	/**
	* CameraComponent interface
	*/
	virtual void OnRegister() final;
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) final;

	/**
	* member variables
	*/
	/** 카메라의 blending 기능을 지원하는 stack */
	UPROPERTY()
	TObjectPtr<UTulCameraModeStack> CameraModeStack;

	/** 현재 CameraMode를 가져오는 Delegate */
	FTulCameraModeDelegate DetermineCameraModeDelegate;
};
