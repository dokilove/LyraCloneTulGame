// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TulAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	UTulAssetManager();

	static UTulAssetManager& Get();

	virtual void StartInitialLoading() final;

	/*
	* 해당 함수는 FScopeLogTime을 사용하지 않을지 유무 판단을 위해 사용 
	* 굳이 클론 코딩할 필요는 없지만, 알아두면 좋은 점들이 있으니 해보자 
	*/
	static bool ShouldLogAssetLoads();

	static UObject* SynchronousLoadAsset(const FSoftObjectPath& AssetPath);

	/*
	* GetAsset은 정적 로딩으로 BP Classㅇ와 Object 로딩 
	* - 주목해야 할 부분은 bKeepInMemory 
	*/
	template<typename AssetType>
	static AssetType* GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	template<typename AssetType>
	static TSubclassOf<AssetType> GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory = true);

	/** [THREAD-SAFE] 메모리에 로딩된 에셋 캐싱 */ 
	void AddLoadedAsset(const UObject* Asset);

	// GC의 대상 
	UPROPERTY()
	TSet<TObjectPtr<const UObject>> LoadedAssets;

	// Object 단위 Locking 
	FCriticalSection SyncObject;
};

template<typename AssetType>
inline AssetType* UTulAssetManager::GetAsset(const TSoftObjectPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	AssetType* LoadedAsset = nullptr;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		// 로딩이 되어있다? -> 바로 가져옴 
		// 로딩이 안되어 있다 -> Null 
		LoadedAsset = AssetPointer.Get();
		if (!LoadedAsset)
		{
			LoadedAsset = Cast<AssetType>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedAsset, TEXT("Failed to load asset [%s]"), *AssetPointer.ToString());
		}

		if (LoadedAsset && bKeepInMemory)
		{
			// 여기서 AddLoadAsset은 메모리에 상주하기 위한 장치라고 생각하면 됨: 
			// - 한번 등록되면 직접 내리지 않는한 Unload가 되지 않음 (== 캐싱) 
			Get().AddLoadedAsset(Cast<UObject>(LoadedAsset));
		}
	}
	return LoadedAsset;
}

template<typename AssetType>
inline TSubclassOf<AssetType> UTulAssetManager::GetSubclass(const TSoftClassPtr<AssetType>& AssetPointer, bool bKeepInMemory)
{
	TSubclassOf<AssetType> LoadedSubclass;

	const FSoftObjectPath& AssetPath = AssetPointer.ToSoftObjectPath();

	if (AssetPath.IsValid())
	{
		LoadedSubclass = AssetPointer.Get();
		if (!LoadedSubclass)
		{
			LoadedSubclass = Cast<UClass>(SynchronousLoadAsset(AssetPath));
			ensureAlwaysMsgf(LoadedSubclass, TEXT("Failed to load asset class [%s]"), *AssetPointer.ToString());
		}

		if (LoadedSubclass && bKeepInMemory)
		{
			Get().AddLoadedAsset(Cast<UObject>(LoadedSubclass));
		}
	}

	return LoadedSubclass;
}
