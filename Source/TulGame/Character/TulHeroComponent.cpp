// Fill out your copyright notice in the Description page of Project Settings.


#include "TulHeroComponent.h"
#include "TulPawnData.h"
#include "TulPawnExtensionComponent.h"
#include "Components/GameFrameworkComponentManager.h"
#include "TulGame/Player/TulPlayerState.h"
#include "TulGame/TulGameplayTags.h"
#include "TulGame/TulLogChannels.h"

const FName UTulHeroComponent::NAME_ActorFeatureName("Hero");

UTulHeroComponent::UTulHeroComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;
}

void UTulHeroComponent::OnRegister()
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

	RegisterInitStateFeature();
}

void UTulHeroComponent::BeginPlay()
{
	Super::BeginPlay();

	// PawnExtensionComponent에 대해서 (PawnExtension Feature) OnActorInitStateChanged() 관찰하도록 (Observing)
	BindOnActorInitStateChanged(UTulPawnExtensionComponent::NAME_ActorFeatureName, FGameplayTag(), false);

	// InitState_Spawned로 초기화
	ensure(TryToChangeInitState(FTulGameplayTags::Get().InitState_Spawned));

	// ForceUpdate 진행
	CheckDefaultInitialization();
}

void UTulHeroComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();

	Super::EndPlay(EndPlayReason);
}

void UTulHeroComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params)
{
	const FTulGameplayTags& InitTags = FTulGameplayTags::Get();
	if (Params.FeatureName == UTulPawnExtensionComponent::NAME_ActorFeatureName)
	{
		// TulPawnExtensionComponent의 DataInitialized 상태 변화 관찰 후, TulHeroComponent도 DataInitialized로 변경
		// - CanChangeInitState 확인
		if (Params.FeatureState == InitTags.InitState_DataInitialized)
		{
			CheckDefaultInitialization();
		}
	}
}

bool UTulHeroComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const
{
	check(Manager);

	const FTulGameplayTags& InitTags = FTulGameplayTags::Get();
	APawn* Pawn = GetPawn<APawn>();
	ATulPlayerState* TulPS = GetPlayerState<ATulPlayerState>();

	// InitState_Spawned 초기화
	if (!CurrentState.IsValid() && DesiredState == InitTags.InitState_Spawned)
	{
		// Pawn이 잘 세팅만 되어있으면 바로 Spawned로 넘어감!
		if (Pawn)
		{
			return true;
		}
	}

	// Spawned -> DataAvailable
	if (CurrentState == InitTags.InitState_Spawned && DesiredState == InitTags.InitState_DataAvailable)
	{
		if (!TulPS)
		{
			return false;
		}

		return true;
	}

	// DataAvailable -> DataInitialized
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		// PawnExtentionComponent가 DataInitialized될 때까지 기다림 (== 모든 Feature Component가 DataAvailable인 상태)
		return TulPS && Manager->HasFeatureReachedInitState(Pawn, UTulPawnExtensionComponent::NAME_ActorFeatureName, InitTags.InitState_DataInitialized);
	}

	// DataInitialized -> GameplayReady
	if (CurrentState == InitTags.InitState_DataInitialized && DesiredState == InitTags.InitState_GameplayReady)
	{
		return true;
	}

	return false;
}

void UTulHeroComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState)
{
	const FTulGameplayTags& InitTags = FTulGameplayTags::Get();

	// DataAvailable -> DataInitialized 단계
	if (CurrentState == InitTags.InitState_DataAvailable && DesiredState == InitTags.InitState_DataInitialized)
	{
		APawn* Pawn = GetPawn<APawn>();
		ATulPlayerState* TulPS = GetPlayerState<ATulPlayerState>();
		if (!ensure(Pawn && TulPS))
		{
			return;
		}

		// Input 과 Camera에 대한 핸들링... (TODO)

		const bool bIsLocallyControlled = Pawn->IsLocallyControlled();
		const UTulPawnData* PawnData = nullptr;
		if (UTulPawnExtensionComponent* PawnExtComp = UTulPawnExtensionComponent::FindPawnExtensionComponent(Pawn))
		{
			PawnData = PawnExtComp->GetPawnData<UTulPawnData>();
		}
	}
}

void UTulHeroComponent::CheckDefaultInitialization()
{
	// 앞서 BindOnActorInitStateChange에서 보았듯이 Hear Feature는 Pawn Extension Feature에 종속되어 있으므로, CheckDefaultInitializationForImplementers 호출하지 않음:

	// ContinueInitStateChain은 앞서 PawnExtComponent와 같음
	const FTulGameplayTags& InitTags = FTulGameplayTags::Get();
	static const TArray<FGameplayTag> StateChain = { InitTags.InitState_Spawned, InitTags.InitState_DataAvailable, InitTags.InitState_DataInitialized, InitTags.InitState_GameplayReady };
	ContinueInitStateChain(StateChain);
}
