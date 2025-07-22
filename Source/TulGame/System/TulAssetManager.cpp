﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "TulAssetManager.h"
#include "TulGame/TulLogChannels.h"

UTulAssetManager::UTulAssetManager()
{
}

UTulAssetManager& UTulAssetManager::Get()
{
	check(GEngine);
	 
	// 우리는 AssetManager를 UEngine의 GEngine의 AssetManager의 Class를 오버라이드 했기 때문에, GEngine에 Asset Manager가 있음 
	if (UTulAssetManager* Singleton = Cast<UTulAssetManager>(GEngine->AssetManager))
	{
		return *Singleton;
	}

	UE_LOG(LogTul, Fatal, TEXT("Invalid AssetManagerClassname in DefaultEngine.ini(project settings); it must be TulAssetManager"));

	// 위의 UE_LOG의 Fatal로 인해, Crash 나기 때문에 도달하지 않지만 컴파일을 위해 더미로 리턴 
	return *NewObject<UTulAssetManager>();
}

PRAGMA_DISABLE_OPTIMIZATION
void UTulAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
}
PRAGMA_ENABLE_OPTIMIZATION

bool UTulAssetManager::ShouldLogAssetLoads()
{
	const TCHAR* CommandLineContent = FCommandLine::Get();
	static bool bLogAssetLoads = FParse::Param(CommandLineContent, TEXT("LogAssetLoads"));
	return bLogAssetLoads;
}

UObject* UTulAssetManager::SynchronousLoadAsset(const FSoftObjectPath& AssetPath)
{
	// 해당 함수를 만든 이유는 'synchronous load asset이 불필요하게 하는 것이 없는지 확인하기 위함' 
	if (AssetPath.IsValid())
	{
		// FScopeLogTime을 확인해보자 
		TUniquePtr<FScopeLogTime> LogTimePtr;
		if (ShouldLogAssetLoads())
		{
			// 단순히 로깅하면서, 초단위로 로깅 진행 
			LogTimePtr = MakeUnique<FScopeLogTime>(*FString::Printf(TEXT("synchronous loaded assets [%s]"), *AssetPath.ToString()), nullptr, FScopeLogTime::ScopeLog_Seconds);
		}

		// 여기서 두가지 분기:
		// 1. AssetManaget가 있으면, AssetManager의 StreamableManager를 통해 정적 로딩 
		// 2. 아니면, FSoftObjectPath를 통해 바로 정적 로딩 
		if (UAssetManager::IsInitialized()) 
		{
			return UAssetManager::GetStreamableManager().LoadSynchronous(AssetPath, false);
		}

		// if asset manager is not ready, use LoadObject() 
		// - 슥 보면, StaticLoadObject가 보인다. 
		// - 참고로, 항상 StaticLoadObject하기 전에 StaticFindObject를 통해 확인하고 실패하면 진짜 로딩함 
		return AssetPath.TryLoad();
	}

	return nullptr;
}

void UTulAssetManager::AddLoadedAsset(const UObject* Asset)
{
	if (ensureAlways(Asset))
	{
		FScopeLock Lock(&SyncObject);
		LoadedAssets.Add(Asset);
	}
}
