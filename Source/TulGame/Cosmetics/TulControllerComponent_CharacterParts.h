// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TulCharacterPartTypes.h"
#include "Components/ControllerComponent.h"
#include "TulControllerComponent_CharacterParts.generated.h"

class UTulPawnComponent_CharacterParts;

/** ControllerComponent가 소유하는 Character Parts */
USTRUCT()
struct FTulControllerCharacterPartEntry
{
	GENERATED_BODY()
	
	/** Character Part에 대한 정의 (메타 데이터 == MetaData) */
	UPROPERTY(EditAnywhere)
	FTulCharacterPart Part;

	/** Character Part 핸들 (고유값) - Controller가 Possess하고 있는 Pawn에서 생성한(인스턴스) Character Part 핸들값 */
	FTulCharacterPartHandle Handle;

};

UCLASS(meta = (BlueprintSpawnableComponent))
class TULGAME_API UTulControllerComponent_CharacterParts : public UControllerComponent
{
	GENERATED_BODY()
	
public:
	UTulControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UTulPawnComponent_CharacterParts* GetPawnCustomizer() const;

	UFUNCTION(BlueprintCallable, Category = Cosmetics)
	void AddCharacterPart(const FTulCharacterPart& NewPart);
	void AddCharacterPartInternal(const FTulCharacterPart& NewPart);

	UPROPERTY(EditAnywhere, Category = Cosmetics)
	TArray<FTulControllerCharacterPartEntry> CharacterParts;
};
