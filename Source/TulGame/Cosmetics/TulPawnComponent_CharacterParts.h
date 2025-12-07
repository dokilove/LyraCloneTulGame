// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "TulCharacterPartTypes.h"
#include "TulCosmeticAnimationTypes.h"
#include "TulPawnComponent_CharacterParts.generated.h"

class UTulPawnComponent_CharacterParts;

/** 인스턴스화 된 Character Part의 단위 */
USTRUCT()
struct FTulAppliedCharacterPartEntry
{
	GENERATED_BODY()

	/** Character Part의 정의(메타 데이터) */
	UPROPERTY()
	FTulCharacterPart Part;

	/** TulCharacterPartList에서 할당 받은 Part 핸들 값 (FTulControllerCharacterPartEntry의 Handle 값과 같아야 함 - > 같으면 같은 Part */
	UPROPERTY()
	int32 PartHandle = INDEX_NONE;

	/** 인스턴스화 된 Character Part용 Actor */
	UPROPERTY()
	TObjectPtr<UChildActorComponent> SpawnedComponent = nullptr;
};

/** TulPawnComponent_CharacterParts에서 실질적 Character Parts를 관리하는 클래스 */
USTRUCT(BlueprintType)
struct FTulCharacterPartList
{
	GENERATED_BODY()

	FTulCharacterPartList() : OwnerComponent(nullptr)
	{}

	FTulCharacterPartList(UTulPawnComponent_CharacterParts* InOwnerComponent) : OwnerComponent(InOwnerComponent)
	{}

	bool SpawnActorForEntry(FTulAppliedCharacterPartEntry& Entry);
	void DestroyActorForEntry(FTulAppliedCharacterPartEntry& Entry);

	FTulCharacterPartHandle AddEntry(FTulCharacterPart NewPart);
	void RemoveEntry(FTulCharacterPartHandle Handle);

	FGameplayTagContainer CollectCombinedTags() const;

	/** 현재 인스턴스화된 Character Part */
	UPROPERTY()
	TArray<FTulAppliedCharacterPartEntry> Entries;

	/** 해당 TulCharacterPartList의 Owner인 PawnComponent */
	UPROPERTY()
	TObjectPtr<UTulPawnComponent_CharacterParts> OwnerComponent;

	/** 앞서 보았던 PartHandle의 값을 할당 및 관리하는 변수 */
	int32 PartHandleCounter = 0;
};

UCLASS()
class TULGAME_API UTulPawnComponent_CharacterParts : public UPawnComponent
{
	GENERATED_BODY()

public:
	UTulPawnComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	USkeletalMeshComponent* GetParentMeshComponent() const;
	USceneComponent* GetSceneComponentToAttachTo() const;
	FGameplayTagContainer GetCombinedTags(FGameplayTag RequiredPrefix) const;
	void BroadcastChanged();

	FTulCharacterPartHandle AddCharacterPart(const FTulCharacterPart& NewPart);
	void RemoveCharacterPart(FTulCharacterPartHandle Handle);

	/** 인스턴스 화 된 Character Parts */
	UPROPERTY()
	FTulCharacterPartList CharacterPartList;

	/** 애니메이션 적용을 위한 메시와 연결고리 */
	UPROPERTY(EditAnywhere, Category = Cosmetics)
	FTulAnimBodyStyleSelectionSet BodyMeshes;
};
