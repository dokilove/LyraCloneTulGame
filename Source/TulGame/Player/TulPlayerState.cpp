// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPlayerState.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "TulGame/AbilitySystem/TulAbilitySystemComponent.h"
#include "TulGame/AbilitySystem/TulAbilitySet.h"
#include "TulGame/AbilitySystem/Attributes/TulHealthSet.h"
#include "TulGame/AbilitySystem/Attributes/TulCombatSet.h"
#include "TulGame/GameModes/TulExperienceManagerComponent.h"
#include "TulGame/GameModes/TulGameModeBase.h"
#include "TulGame/Character/TulPawnData.h"

ATulPlayerState::ATulPlayerState(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	AbilitySystemComponent = ObjectInitializer.CreateDefaultSubobject<UTulAbilitySystemComponent>(this, TEXT("AbilitySystemComponent"));

	CreateDefaultSubobject<UTulHealthSet>(TEXT("HealthSet"));
	CreateDefaultSubobject<UTulCombatSet>(TEXT("CombatSet"));
}

void ATulPlayerState::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	check(AbilitySystemComponent);
	// 아래의 코드는 우리가 InitAbilityActorInfo를 재호출을 통하는 이유를 설명하는 코드이다:
	{
		// 처음  InitAbilityActorInfo를 호출 당시, OwnerActor와 AvatarActor 가 같은 Actor를 가르키고 있으며, 이것은 PlayerState이다
		// - OwnerActor는 PlayerState가 의도하는게 맞지만, AvatarActor는 PlayerController가 소유하는 대상인 Pawn이 되어야 한다!
		// - 이를 위해 재 세팅을 해준다
		FGameplayAbilityActorInfo* ActorInfo = AbilitySystemComponent->AbilityActorInfo.Get();
		check(ActorInfo->OwnerActor == this);
		check(ActorInfo->OwnerActor == ActorInfo->AvatarActor);
	}
	// 이 시점에서는 GetPawn은 nullptr이지만 일단 넣어준다 나중에 재 세팅할거다
	AbilitySystemComponent->InitAbilityActorInfo(this, GetPawn());

	const AGameStateBase* GameState = GetWorld()->GetGameState();
	check(GameState);

	UTulExperienceManagerComponent* ExperienceManagerComponent = GameState->FindComponentByClass<UTulExperienceManagerComponent>();
	check(ExperienceManagerComponent);

	ExperienceManagerComponent->CallOrRegister_OnExperienceLoaded(FOnTulExperienceLoaded::FDelegate::CreateUObject(this, &ThisClass::OnExperienceLoaded));
}

void ATulPlayerState::OnExperienceLoaded(const UTulExperienceDefinition* CurrentExperience)
{
	if (ATulGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ATulGameModeBase>())
	{
		// ATulGameModeBase에서 GetPawnDataForController를 구현해야 함
		// - GetPawnDataForController에서 우리는 아직 PawnData를 설정하지 않았으므로, ExperienceManagerComponent의 DefaultPawnData로 설정한다
		const UTulPawnData* NewPawnData = GameMode->GetPawnDataForController(GetOwningController());
		check(NewPawnData);

		SetPawnData(NewPawnData);
	}
}

void ATulPlayerState::SetPawnData(const UTulPawnData* InPawnData)
{
	check(InPawnData);

	// PawnData가 두번 설정되는 것은 원하지 않음
	check(!PawnData);

	PawnData = InPawnData;

	// PawnData의 AbilitySet을 순회하며, ASC에 Ability를 할당(Give)한다
	// - 이 과정에서 ASC의 AcitivatableAbilities에 추가된다
	for (UTulAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}
}
