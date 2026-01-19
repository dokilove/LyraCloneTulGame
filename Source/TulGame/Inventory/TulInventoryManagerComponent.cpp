// Fill out your copyright notice in the Description page of Project Settings.


#include "TulInventoryManagerComponent.h"
#include "TulInventoryItemDefinition.h"
#include "TulInventoryItemInstance.h"


UTulInventoryItemInstance* FTulInventoryList::AddEntry(TSubclassOf<UTulInventoryItemDefinition> ItemDef)
{
	UTulInventoryItemInstance* Result = nullptr;
	check(ItemDef);
	check(OwnerComponent);

	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());

	FTulInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<UTulInventoryItemInstance>(OwningActor);
	NewEntry.Instance->ItemDef = ItemDef;

	Result = NewEntry.Instance;
	return Result;
}

UTulInventoryManagerComponent::UTulInventoryManagerComponent(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
	, InventoryList(this)
{
}

UTulInventoryItemInstance* UTulInventoryManagerComponent::AddItemDefinition(TSubclassOf<UTulInventoryItemDefinition> ItemDef)
{
	UTulInventoryItemInstance* Result = nullptr;
	if (ItemDef)
	{
		Result = InventoryList.AddEntry(ItemDef);
	}
	return Result;
}
