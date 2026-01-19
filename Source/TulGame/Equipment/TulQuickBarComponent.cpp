// Fill out your copyright notice in the Description page of Project Settings.


#include "TulQuickBarComponent.h"

UTulQuickBarComponent::UTulQuickBarComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UTulQuickBarComponent::BeginPlay()
{
	// NumSlots에 따라 미리 Slots를 할당한다
	if (Slots.Num() < NumSlots)
	{
		Slots.AddDefaulted(NumSlots - Slots.Num());
	}

	Super::BeginPlay();
}

void UTulQuickBarComponent::AddItemToSlot(int32 SlotIndex, UTulInventoryItemInstance* Item)
{
	// 해당 로직을 보면  Slots는 Add로 동적추가가 아닌, Index에 바로 넣는다
	// - 그럼 미리 Pre-size로 했다는 것인데 이는 BeginPlay()에서 진행한다
	if (Slots.IsValidIndex(SlotIndex) && (Item != nullptr))
	{
		if (Slots[SlotIndex] == nullptr)
		{
			Slots[SlotIndex] = Item;
		}
	}
}
