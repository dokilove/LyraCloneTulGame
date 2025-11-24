// Fill out your copyright notice in the Description page of Project Settings.


#include "TulControllerComponent_CharacterParts.h"
#include "TulPawnComponent_CharacterParts.h"

UTulControllerComponent_CharacterParts::UTulControllerComponent_CharacterParts(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

PRAGMA_DISABLE_OPTIMIZATION
UTulPawnComponent_CharacterParts* UTulControllerComponent_CharacterParts::GetPawnCustomizer() const
{
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		// 생각해보면, 우리는 앞서 TulPawnComponent_CharacterParts를 상속받는 B_MannequinPawnCosmetics를 이미 B_Hero_ShooterMannequin에 추가 헀다
		// B_MannequinPawnCosmetics를 반환되기를 기대한다
		return ControlledPawn->FindComponentByClass<UTulPawnComponent_CharacterParts>();
	}
	return nullptr;
}
PRAGMA_ENABLE_OPTIMIZATION

void UTulControllerComponent_CharacterParts::AddCharacterPart(const FTulCharacterPart& NewPart)
{
	AddCharacterPartInternal(NewPart);
}

void UTulControllerComponent_CharacterParts::AddCharacterPartInternal(const FTulCharacterPart& NewPart)
{
	FTulControllerCharacterPartEntry& NewEntry = CharacterParts.AddDefaulted_GetRef();
	NewEntry.Part = NewPart;

	if (UTulPawnComponent_CharacterParts* PawnCustomizer = GetPawnCustomizer())
	{
		NewEntry.Handle = PawnCustomizer->AddCharacterPart(NewPart);
	}
}
