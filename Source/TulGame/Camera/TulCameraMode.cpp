// Fill out your copyright notice in the Description page of Project Settings.


#include "TulCameraMode.h"
#include "TulPlayerCameraManager.h"
#include "TulCameraComponent.h"

FTulCameraModeView::FTulCameraModeView()
	: Location(ForceInit)
	, Rotation(ForceInit)
	, ControlRotation(ForceInit)
	, FieldOfView(TUL_CAMERA_DEFAULT_FOV)
{

}

void FTulCameraModeView::Blend(const FTulCameraModeView& Other, float OtherWeight)
{
	if (OtherWeight <= 0.0f)
	{
		return;
	}
	else if (OtherWeight >= 1.0f)
	{
		// Weight가 1.0이면 Other를 덮어쓰면 된다
		*this = Other;
		return;
	}

	// Location + OtherWeight * (Other.Location - Location);
	Location = FMath::Lerp(Location, Other.Location, OtherWeight);

	// Location과 같은 방식 Lerp(ControlRotation과 FieldOfView도 같음)
	const FRotator DeltaRotation = (Other.Rotation - Rotation).GetNormalized();
	Rotation = Rotation + (OtherWeight * DeltaRotation);

	const FRotator DeltaControlRotation = (Other.ControlRotation - ControlRotation).GetNormalized();
	ControlRotation = ControlRotation + (OtherWeight * DeltaControlRotation);

	FieldOfView = FMath::Lerp(FieldOfView, Other.FieldOfView, OtherWeight);
}

UTulCameraMode::UTulCameraMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	FieldOfView = TUL_CAMERA_DEFAULT_FOV;
	ViewPitchMin = TUL_CAMERA_DEFAULT_PITCH_MIN;
	ViewPitchMax = TUL_CAMERA_DEFAULT_PITCH_MAX;

	BlendTime = 0.0f;
	BlendAlpha = 1.0f;
	BlendWeight = 1.0f;

	BlendFunction = ETulCameraModelBlendFunction::EaseOut;
	BlendExponent = 4.0f;
}

void UTulCameraMode::UpdateCameraMode(float DeltaTime)
{
	// Actor를 활용하여, Pivot[Location|Rotation]을 계산하여 View를 업데이트
	UpdateView(DeltaTime);

	// BlendWeight를 DeltaTime을 활용하여, BlendAlpha 계산 후, BlendFunction에 맞게 재-매핑하여 최종계산
	UpdateBlending(DeltaTime);
}

void UTulCameraMode::UpdateView(float DeltaTime)
{
	// CameraMode를 가지고 있는 CameraComponent의 Owner인 Character(Pawn)을 활용하여, PivotLocation/Rotation을 반환함
	FVector PivotLocation = GetPivotLocation();
	FRotator PivotRotation = GetPivotRotation();

	// pitch 값에 대해 Min/Max를 Clamp시킴
	PivotRotation.Pitch = FMath::ClampAngle(PivotRotation.Pitch, ViewPitchMin, ViewPitchMax);

	// FTulCameraModeView에 PivotLocation/Rotation 설정
	View.Location = PivotLocation;
	View.Rotation = PivotRotation;

	// PivotRotation을 똑같이 ControlRotation으로 활용
	View.ControlRotation = View.Rotation;
	View.FieldOfView = FieldOfView;

	// 정리하면 Character의 Location과 ControlRotation을 활용하여, View를 업데이트 함
}

void UTulCameraMode::UpdateBlending(float DeltaTime)
{
	// BlendAlpha를 DeltaTime을 통해 계산
	if (BlendTime > 0.f)
	{
		// BlendTime은 Blending 과정 총 시간(초)
		// - BlendAlpha는 0 -> 1로 변화하는 과정:
		// - DeltaTime을 활용하여, BlendTime을 1로 볼 경우, 진행 정도를 누적
		BlendAlpha += (DeltaTime / BlendTime);
	}
	else
	{
		BlendAlpha = 1.0f;
	}

	// BlendWeight를 [0,1]를 BlendFunction에 맞게 재매핑
	const float Exponent = (BlendExponent > 0.0f) ? BlendExponent : 1.0f;
	switch (BlendFunction)
	{
	case ETulCameraModelBlendFunction::Linear:
		BlendWeight = BlendAlpha;
		break;
	case ETulCameraModelBlendFunction::EaseIn:
		BlendWeight = FMath::InterpEaseIn(0.0f, 1.0f, BlendAlpha, Exponent);
		break;
	case ETulCameraModelBlendFunction::EaseOut:
		BlendWeight = FMath::InterpEaseOut(0.0f, 1.0f, BlendAlpha, Exponent);
		break;
	case ETulCameraModelBlendFunction::EaseInOut:
		BlendWeight = FMath::InterpEaseInOut(0.0f, 1.0f, BlendAlpha, Exponent);
		break;
	default:
		checkf(false, TEXT("UpdateBlending: Invalid BlendFunction [%d]\n"), (uint8)BlendFunction);
		break;
	}
}

UTulCameraComponent* UTulCameraMode::GetTulCameraComponent() const
{
	// 우리가 앞서 UTulCameraMode를 생성하는 곳은 UTulCameraModeStack이었다
	// - 해당 코드를 보면, GetOuter()를 TulCameraMode로 TulCameraComponent로 설정하였다
	// - UTulCameraModeStack::GetCameraModeInstance() 확인
	return CastChecked<UTulCameraComponent>(GetOuter());
}

AActor* UTulCameraMode::GetTargetActor() const
{
	const UTulCameraComponent* TulCameraComponent = GetTulCameraComponent();
	return TulCameraComponent->GetTargetActor();
}

FVector UTulCameraMode::GetPivotLocation() const
{
	const AActor* TargetActor = GetTargetActor();
	check(TargetActor);

	if (const APawn* TargetPawn = Cast<APawn>(TargetActor))
	{
		// BaseEyeHeight를 고려하여, ViewLocation을 반환함
		return TargetPawn->GetPawnViewLocation();
	}

	return TargetActor->GetActorLocation();
}

FRotator UTulCameraMode::GetPivotRotation() const
{
	const AActor* TargetActor = GetTargetActor();
	check(TargetActor);

	if (const APawn* TargetPawn = Cast<APawn>(TargetActor))
	{
		// GetViewRotation() 확인, 보통 Pawn의 ControlRotation을 반환
		return TargetPawn->GetViewRotation();
	}

	return TargetActor->GetActorRotation();
}
 
UTulCameraModeStack::UTulCameraModeStack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

UTulCameraMode* UTulCameraModeStack::GetCameraModeInstance(TSubclassOf<UTulCameraMode>& CameraModeClass)
{
	check(CameraModeClass);

	// CameraModeInstance에서 먼저 생성되어 있는지 확인 후, 반환한다
	for (UTulCameraMode* CameraMode : CameraModeInstances)
	{
		// CameraMode는 UClass를 비교한다
		// - CameraMode는 클래스 타입에 하나만 생기게 된다
		if ((CameraMode != nullptr) && (CameraMode->GetClass() == CameraModeClass))
		{
			return CameraMode;
		}
	}

	// CameraModeClass에 알맞는 CameraMode의 인스탄스가 없다면 생성한다
	UTulCameraMode* NewCameraMode = NewObject<UTulCameraMode>(GetOuter(), CameraModeClass, NAME_None, RF_NoFlags);
	check(NewCameraMode);

	// 여기서 우리는 CameraModeInstance는 CameraModeClass에 맞는 인스턴스를 가지고(관리하는) 컨테이너라는 것을 알 수 있다
	CameraModeInstances.Add(NewCameraMode);

	return NewCameraMode;
}

void UTulCameraModeStack::PushCameraMode(TSubclassOf<UTulCameraMode>& CameraModeClass)
{ 
	if (!CameraModeClass)
	{
		return;
	}

	UTulCameraMode* CameraMode = GetCameraModeInstance(CameraModeClass);
	check(CameraMode);

	int32 StackSize = CameraModeStack.Num();
	if ((StackSize > 0) && (CameraModeStack[0] == CameraMode))
	{
		// CameraModeStack[0] 가장 최근에 이미 CameraMode가 Stacking 되었으므로 그냥 리턴!
		return;
	}

	// ExistingStackIndex는 CameraModeStack에서 CameraMode에 맞는 Index를 찾음
	// ExistingStackContribution은 위에서 아래로 최종 BlendWeight 값을 찾기 위해 초기값으로 1.0으로 설정
	int32 ExistingStackIndex = INDEX_NONE;
	float ExistingStackContribution = 1.0f;

	/**
	* BlendWeight		| ExistingStackContribution			| ExistingStackContribution (accumulated)
	* 0.1f				| (1.0f) * 0.1f = 0.1f				| (1.0f - 0.1f) = 0.9f
	* 0.3f				| (0.9f) * 0.3f = 0.27f				| (1.0f - 0.3f) * 0.9f = 0.63f
	* 0.6f				| (0.63f) * 0.6f = 0.378f			| (1.0f - 0.6f) * 0.63f = 0.252f
	* 1.0f				| (0.252f) * 1.0f = 0.252f			| 
	*					| 0.1f + 0.27f + 0.378f + 0.252f = 1.0f!
	*/

	for (int32 StackIndex = 0; StackIndex < StackSize; ++StackIndex)
	{
		if (CameraModeStack[StackIndex] == CameraMode)
		{
			ExistingStackIndex = StackIndex;
			// BlendWeight를 CameraMode에 추가해주자
			// - 여기서 ExistingStackContribution 우리가 찾는 CameraMode를 찾았으니깐, 누적된 BlendWeight와 함께 BlendWeight를 곱하여, 루프를 빠져나온다
			ExistingStackContribution *= CameraMode->BlendWeight;
			break;
		}
		else
		{
			// 당연히 우리가 원하는 CameraMode가 아니니깐, InvBlendWeight = (1.0 - BlendWeight)를 곱해줘야, 값이 누적되겠지?
			ExistingStackContribution *= (1.0f - CameraModeStack[StackIndex]->BlendWeight);
		}
	}
	// 해당 루프의 동작 원리는 앞서 적어놓은 표를 확인해보며 이해해보자

	// 우리는 CameraMode를 Top으로 반영하기 위해, 당연히 중간에 있었다면, 제거하여 다시 Push해줘야 한다
	if (ExistingStackIndex != INDEX_NONE)
	{
		CameraModeStack.RemoveAt(ExistingStackIndex);
		StackSize--;
	}
	else
	{
		// 없었으니까 당연히 Contribution은 0으로 세팅해줘야겠지?
		ExistingStackContribution = 0.0f;
	}

	// BlendTime이 0보다 크다는 것은 Blend를 얼마 시간동안 진행함을 의미 따라서, ExistingStackContribution을 적용
	// - 따라서 Blend하지 않는다면, BlendWeight를 1.0을 넣어 새로 넣는 CameraMode만 적용할 것이다
	const bool bShouldBlend = ((CameraMode->BlendTime > 0.f) && (StackSize > 0));
	const float BlendWeight = (bShouldBlend ? ExistingStackContribution : 1.0f);
	CameraMode->BlendWeight = BlendWeight;

	// Array를 Stack처럼 사용하는 것은 알지만, Index 0에 넣는 것은 비효율 적인데
	// - Push, Pop 메서드와 같이 그냥 last에 넣는게 어떨까 싶음
	CameraModeStack.Insert(CameraMode, 0);

	// 앞서 설명했듯이 마지막은 항상 1.0이 되어야 함
	CameraModeStack.Last()->BlendWeight = 1.0f;
}

void UTulCameraModeStack::EvaluateStack(float DeltaTime, FTulCameraModeView& OutCameraModeView)
{
	// Top -> Bottom [0 -> Num]까지 순차적으로 Stack에 있는 CameraMode 업데이트
	UpdateStack(DeltaTime);

	// Bottom -> Top까지 CameraModeStack에 대해 Blending 진행
	BlendStack(OutCameraModeView);
}

void UTulCameraModeStack::UpdateStack(float DeltaTime)
{
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
	{
		return;
	}

	// CameraModeStack을 순회하며, CameraMode를 업데이트한다
	int32 RemoveCount = 0;
	int32 RemoveIndex = INDEX_NONE;
	for (int32 StackIndex = 0; StackIndex < StackSize; ++StackIndex)
	{
		UTulCameraMode* CameraMode = CameraModeStack[StackIndex];
		check(CameraMode);

		// UpdateCameraMode를 확인해보자
		CameraMode->UpdateCameraMode(DeltaTime);

		// 만약 하나라도 CameraMode가 BlendWeight가 1.0에 도달했다면, 그 이후 CameraMode를 제거한다
		if (CameraMode->BlendWeight >= 1.0f)
		{
			RemoveIndex = (StackIndex + 1);
			RemoveCount = (StackSize - RemoveIndex);
			break;
		}
	}

	if (RemoveCount > 0)
	{
		// 생각해보면 이거 때문에 Pop하고 Push를 안한 것일지도
		CameraModeStack.RemoveAt(RemoveIndex, RemoveCount);
	}
}

void UTulCameraModeStack::BlendStack(FTulCameraModeView& OutCameraModeView)
{
	const int32 StackSize = CameraModeStack.Num();
	if (StackSize <= 0)
	{
		return;
	}

	// CameraModeStack은 Bottom -> Top 순서로 Blend를 진행한다
	const UTulCameraMode* CameraMode = CameraModeStack[StackSize - 1];
	check(CameraMode);

	// 참고로 가장 아래 (Bottom)은 BlendWeight가 1.0dlek
	OutCameraModeView = CameraMode->View;

	// 이미 Index = [StackSize - 1] 이미 OutCameraModeView로 지정했으므로, StackSize - 2부터 순회하면 된다
	for (int32 StackIndex = (StackSize - 2); StackIndex >= 0; --StackIndex)
	{
		CameraMode = CameraModeStack[StackIndex];
		check(CameraMode);

		// TulCameraModeView Blend 함수를 구현하자
		OutCameraModeView.Blend(CameraMode->View, CameraMode->BlendWeight);
	}


}
