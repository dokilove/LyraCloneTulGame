// Fill out your copyright notice in the Description page of Project Settings.


#include "TulInventoryFragment_SetStats.h"
#include "TulInventoryItemInstance.h"

void UTulInventoryFragment_SetStats::OnInstanceCreated(UTulInventoryItemInstance* Instance) const
{
	// iterating InitialItemStats and add stat tag to InventoryItemInstance
	for (const auto& InitialItemStat : InitialItemStats)
	{
		Instance->AddStatTagStack(InitialItemStat.Key, InitialItemStat.Value);
	}
}
