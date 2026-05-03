// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "GameplayTagContainer.h"
#include "GameFeatureAction_WorldActionBase.h"
#include "GameFeatureAction_AddWidgets.generated.h"

/** forward declarations */
struct FComponentRequestHandle;

/** HUD의 Layout 요청 */
USTRUCT()
struct FTulHUDLayoutRequest
{
	GENERATED_BODY()
	/** UI의 레이아웃으로 CommonActivatableWidget을 사용 */
	UPROPERTY(EditAnywhere, Category = UI)
	TSoftClassPtr<UCommonActivatableWidget> LayoutClass;

	/** 앞서 보았던 PrimaryGameLayout의 LayerID를 의미 */
	UPROPERTY(EditAnywhere, Category = UI)
	FGameplayTag LayerID;
};

USTRUCT()
struct FTulHUDElementEntry
{
	GENERATED_BODY()
	/** TulHUDLayout 위에 올릴 대상이 되는 Widget Class */
	UPROPERTY(EditAnywhere, Category = UI)
	TSoftClassPtr<UUserWidget> WidgetClass;

	/** SlotID는  TulHUDLayoutRequest에 올린 LayoutClass에 정의된 Slot(GameplayTag)를 의미*/
	UPROPERTY(EditAnywhere, Category = UI)
	FGameplayTag SlotID;
};

/**
 * 
 */
UCLASS()
class TULGAME_API UGameFeatureAction_AddWidgets : public UGameFeatureAction_WorldActionBase
{
	GENERATED_BODY()
public:
	struct FPerContextData
	{
		TArray<TSharedPtr<FComponentRequestHandle>> ComponentRequests;
		TArray<TWeakObjectPtr<UCommonActivatableWidget>> LayoutsAdded;

		/** Lyra 에서 HUDElement 는 UIExtension으로 관린된다 */
		//TArray<FUIExtensionHandle> ExtensionHandles;
	};

	/**
	* GFA_AddWidget은 형태를 정의하는 Layout과 Layout 위에 올릴 Widget 객체 Widgets으로 구성된다
	*/
	UPROPERTY(EditAnywhere, Category=UI)
	TArray<FTulHUDLayoutRequest> Layout;

	UPROPERTY(EditAnywhere, Category=UI)
	TArray<FTulHUDElementEntry> Widgets;
	
};
