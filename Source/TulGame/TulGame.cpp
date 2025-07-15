// Copyright Epic Games, Inc. All Rights Reserved.

#include "TulGame.h"
#include "TulLogChannels.h"
#include "Modules/ModuleManager.h"

class FTulGameModule : public FDefaultGameModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FTulGameModule::StartupModule()
{
	FDefaultGameModuleImpl::StartupModule();
	UE_LOG(LogTul, Warning, TEXT("StartupModule!"));
}

void FTulGameModule::ShutdownModule()
{
	FDefaultGameModuleImpl::ShutdownModule();
}

IMPLEMENT_PRIMARY_GAME_MODULE(FTulGameModule, TulGame, "TulGame" );
