// Fill out your copyright notice in the Description page of Project Settings.


#include "TulCameraComponent.h"
#include "TulCameraMode.h"

UTulCameraComponent::UTulCameraComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), CameraModeStack(nullptr)
{

}

void UTulCameraComponent::OnRegister()
{
	Super::OnRegister();

	if (!CameraModeStack)
	{
		// 초기화 (BeginPlay와 같은)가 딱히 필요없는 객체로 NewObject로 할당
		CameraModeStack = NewObject<UTulCameraModeStack>(this);
	}
}

void UTulCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	check(CameraModeStack);

	UpdateCameraModes();

	// EvaluteStack은 CameraModeStack에 있는 CameraMode를 업데이트 (+블렌딩)하고 CameraModeStack을 Bottom-Top까지 업데이트된 CameraMode들을 Lerp를 진행해줌
	// - 이에 대한 결과는 CameraModeView에 캐싱된다
	FTulCameraModeView CameraModeView;
	CameraModeStack->EvaluateStack(DeltaTime, CameraModeView);
}

void UTulCameraComponent::UpdateCameraModes()
{
	check(CameraModeStack);

	// DetermineCameraModeDelegate는 CameraMode Class를 반환한다
	// - 해당 Delegate는 HeroComponent의 멤버 함수로 바인딩되어 있다.
	if (DetermineCameraModeDelegate.IsBound())
	{
		if (TSubclassOf<UTulCameraMode> CameraMode = DetermineCameraModeDelegate.Execute())
		{
			CameraModeStack->PushCameraMode(CameraMode);
		}
	}
}
