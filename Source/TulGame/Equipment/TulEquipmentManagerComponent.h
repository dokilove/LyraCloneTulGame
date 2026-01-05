// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "TulEquipmentManagerComponent.generated.h"

/** forward declarations */
class UTulEquipmentDefinition;
class UTulEquipmentInstance;

USTRUCT(BlueprintType)
struct FTulAppliedEquipmentEntry
{
	GENERATED_BODY()

	/** 장착물에 대한 메타 데이터 */
	UPROPERTY()
	TSubclassOf<UTulEquipmentDefinition> EquipmentDefinition;

	/** EquipmentDefinition을 통해 생성된 인스턴스 */
	UPROPERTY()
	TObjectPtr<UTulEquipmentInstance> Instance = nullptr;
};

/**
* 참고로 EquipmentInstance의 인스턴스를 Entry에서 관리하고 있다:
* - TulEquipmentList는 생성된 객체를 관리한다고 보면 된다
*/
USTRUCT(BlueprintType)
struct FTulEquipmentList
{
	GENERATED_BODY()

	FTulEquipmentList(UActorComponent* InOwnerComponent = nullptr) : OwnerComponent(InOwnerComponent)
	{}

	/** 장착물에 대한 관리 리스트 */
	UPROPERTY()
	TArray<FTulAppliedEquipmentEntry> Entries;

	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};

/**
 * 
 */
UCLASS()
class TULGAME_API UTulEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()
	
public:
	UTulEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY()
	FTulEquipmentList EquipmentList;
};
