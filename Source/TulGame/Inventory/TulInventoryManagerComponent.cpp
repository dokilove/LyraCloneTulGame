// Fill out your copyright notice in the Description page of Project Settings.


#include "TulInventoryManagerComponent.h"

UTulInventoryManagerComponent::UTulInventoryManagerComponent(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
	, InventoryList(this)
{
}
