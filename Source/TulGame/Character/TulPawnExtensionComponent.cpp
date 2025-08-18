// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "TulGame/TulGameplayTags.h"
#include "TulGame/TulLogChannels.h"

/** feature name을 component 단위니깐 component를 빼고 pawn extension만 넣은 것을 확인할 수 있다 */
const FName UTulPawnExtensionComponent::NAME_ActorFeatureName("PawnExtension");

UTulPawnExtensionComponent::UTulPawnExtensionComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

PRAGMA_DISABLE_OPTIMIZATION
void UTulPawnExtensionComponent::OnRegister()
{
	Super::OnRegister();

	// 올바른 Actor에 등록되었는지 확인:
	{
		if (!GetPawn<APawn>())
		{
			UE_LOG(LogTul, Error, TEXT("this component has been added to a BP whose base class is not a Pawn!"));
			return;
		}
	}

	// GameFrameworkComponentManager에 InitState 사용을 위해 등록 진행:
	// - 등록은 상속받았던 IGameFrameworkInitStateInterface 메서드 RegisterInitStateFeature()를 활용
	// - 해당 함수를 간단히 보기
	RegisterInitStateFeature();

	// 디버깅을 위한 함수
	UGameFrameworkComponentManager* Manager = UGameFrameworkComponentManager::GetForActor(GetOwningActor());
}
PRAGMA_ENABLE_OPTIMIZATION

void UTulPawnExtensionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// FeatureName에 NAME_None을 넣으면, Actor에 등록된 Feature Component의 InitState 상태를 관찰하겠다는 의미:
	BindOnActorInitStateChanged(NAME_None, FGameplayTag(), false);
	// NAME_None은 등록된 모든 Component를 관찰하겠다
	// FGameplayTag()는 모든 상태변화를 관찰
	// BindOnActorInitStateChanged("PawnExtension", FTulGameplayTags::Get().InitState_DataInitialized, false);
	// PawnExtension가 DataInitialized로 넘어가는 단계일 때 관찰해달라는 뜻

	// InitState_Spawned로 상태 변환:
	// - TryToChangeInitState는 아래와 같이 진행된다:
	//	1. CanChangeInitState로 상태 변환 가능성 유무 판단
	//	2. HandleChangeInitState로 내부 상태 변경 (Feature Component)
	//	3. BindOnActorInitStateChanged로 Bind된 Delegate를 조건에 맞게 호출해 줌
	//		- TulPawnExtensionComponent의 경우, 모든 Actor의 Feature 상태 변화에 대해 OnActorInitStateChanged가 호출됨
	ensure(TryToChangeInitState(FTulGameplayTags::Get().InitState_Spawned));

	// 해당 함수는 우리가 오버라이딩 한다:
	// - 이 함수는 ForceUpdateInitState와 같은 느낌으로 이해해주면 된다
	// - 현재 강제 업데이트 진행 (물론 CanChangeInitState와 HandleChangeInitState를 진행해준다)
	CheckDefaultInitialization();
}

void UTulPawnExtensionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// 앞서, OnRegister의 RegisterInitStateFeature()의 쌍을 맞추어주자
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UTulPawnExtensionComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	IGameFrameworkInitStateInterface::OnActorInitStateChanged(Params);
}

bool UTulPawnExtensionComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	return IGameFrameworkInitStateInterface::CanChangeInitState(Manager, CurrentState, DesiredState);
}

void UTulPawnExtensionComponent::CheckDefaultInitialization()
{
	// PawnExtensionComponent는 Feature Component들의 초기화를 관장하는 Component이다:
	// - 따라서, Actor에 바인딩된 Feature Component들에 대해 CheckDefaultInitialization을 호출해주도록 한다 (ForceUpdate 느낌?)
	// - 이 메서드를 IGameFrameworkInitStateInterface가 제공하는데, CheckDefaultInitializationForImplemneters이다:
	// - 간단히 CheckDefaultInitializationForImplementers 보자:
	CheckDefaultInitializationForImplementers();

	const FTulGameplayTags& InitTags = FTulGameplayTags::Get();

	// 사용자 정의 InitState를 직접 넘겨줘야 한다...
	static const TArray<FGameplayTag> StateChain = { InitTags.InitState_Spawned, InitTags.InitState_DataAvailable, InitTags.InitState_DataInitialized, InitTags.InitState_GameplayReady };

	// CanChangeInitState()와 HandleChangeInitState() 그리고 ChangeFeatureInitState 호출을 통한 OnActorInitStateChanged Delegate 호출까지 진행해준다:
	// 아래의 코드를 간단히 보자:
	// - 해당 코드까지 보면, 우리는 간단히 짐작할 수 있다:
	//	- 계속 상태를 가능할 때까지 한 번 업데이트 한다
	//	- InitState에 대한 변화는 Linear(선형적)임을 -> 나중에 Diagram으로 정리하면서 보자
	//		- 업데이트가 멈추면 누군가 시작해줘야 함을 의미 (chaining)
	ContinueInitStateChain(StateChain);
}
