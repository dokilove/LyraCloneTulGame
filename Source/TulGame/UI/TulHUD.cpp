// Fill out your copyright notice in the Description page of Project Settings.


#include "TulHUD.h"
#include "Components/GameFrameworkComponentManager.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(TulHUD)

ATulHUD::ATulHUD(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void ATulHUD::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	// TulHUD를 Receiver로 Actor를 추가하자
	UGameFrameworkComponentManager::AddGameFrameworkComponentReceiver(this);
}

void ATulHUD::BeginPlay()
{
	UGameFrameworkComponentManager::SendGameFrameworkComponentExtensionEvent(this, UGameFrameworkComponentManager::NAME_GameActorReady);
	Super::BeginPlay();
}

void ATulHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UGameFrameworkComponentManager::RemoveGameFrameworkComponentReceiver(this);
	Super::EndPlay(EndPlayReason);
}
