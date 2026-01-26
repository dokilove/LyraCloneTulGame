// Fill out your copyright notice in the Description page of Project Settings.


#include "TulQuickBarComponent.h"
#include "TulEquipmentDefinition.h"
#include "TulEquipmentInstance.h"
#include "TulEquipmentManagerComponent.h"
#include "TulGame/Inventory/TulInventoryItemInstance.h"
#include"TulGame/Inventory/TulInventoryFragment_EquippableItem.h"

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

UTulEquipmentManagerComponent* UTulQuickBarComponent::FindEquipmentManager() const
{
	if (AController* OwnerController = Cast<AController>(GetOwner()))
	{
		if (APawn* Pawn = OwnerController->GetPawn())
		{
			return Pawn->FindComponentByClass<UTulEquipmentManagerComponent>();
		}
	}
	return nullptr;
}

void UTulQuickBarComponent::UnequipItemInSlot()
{
	// 참고로 QuickBar는 Controller에 붙어있는 Component지만, EquipmentManagerComponent는 Controller가 소유(Possess)하고 있다
	if (UTulEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
	{
		// 현재 장착된 Item에 있다면,
		if (EquippedItem)
		{
			// EquipmentManager를 통해, Pawn의 장비를 해제시킨다
			EquipmentManager->UnequipItem(EquippedItem);

			// 그리고 Controller에도 EquipItem의 상태를 없는 것으로 업데이트한다
			EquippedItem = nullptr;
		}
	}
}

void UTulQuickBarComponent::EquipItemInSlot()
{
	check(Slots.IsValidIndex(ActiveSlotIndex));
	check(EquippedItem == nullptr);

	// 현재 활성화된 ActiveSlotIndex를 활용하여 활성화된 InventoryItemInstance를 찾는다
	if (UTulInventoryItemInstance* SlotItem = Slots[ActiveSlotIndex])
	{
		// Slot Item을 통해 (InventoryItemInstance) InventoryFragment_EquippableItem의 Fragment를 찾는다:
		// - 찾는 것이 실패했다면, 장착할 수 없는 Inventory Item임을 의미한다
		if (const UTulInventoryFragment_EquippableItem* EquipInfo = SlotItem->FindFragmentByClass<UTulInventoryFragment_EquippableItem>())
		{
			// EquippableItem에서 EquipmentDefinition을 찾는다:
			// - EquipmentDefinition이 있어야, 장착할 수 있다
			TSubclassOf<UTulEquipmentDefinition> EquipDef = EquipInfo->EquipmentDefinition;
			if (EquipDef)
			{
				// 아래는 Unequip이랑 비슷하게 EquipmentManager를 통해 장착한다
				if (UTulEquipmentManagerComponent* EquipmentManager = FindEquipmentManager())
				{
					EquippedItem = EquipmentManager->EquipItem(EquipDef);
					if (EquippedItem)
					{
						// EquippedItem에는 앞서 보았던 Instigator로 Slot을 대상으로 넣는다
						EquippedItem->Instigator = SlotItem;
					}
				}
			}
		}
	}
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

void UTulQuickBarComponent::SetActiveSlotIndex(int32 NewIndex)
{
	if (Slots.IsValidIndex(NewIndex) && (ActiveSlotIndex != NewIndex))
	{
		// UnequipItem/EquipItem을 통해, NewIndex를 통해 할당된 Item을 장착 및 업데이트를 진행한다
		UnequipItemInSlot();
		ActiveSlotIndex = NewIndex;
		EquipItemInSlot();
	}
}
