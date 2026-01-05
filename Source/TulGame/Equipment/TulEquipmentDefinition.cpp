// Fill out your copyright notice in the Description page of Project Settings.


#include "TulEquipmentDefinition.h"
#include "TulEquipmentInstance.h"

UTulEquipmentDefinition::UTulEquipmentDefinition(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// 기본값으로, TulEquipmentInstance로 설정
	InstanceType = UTulEquipmentInstance::StaticClass();
}
