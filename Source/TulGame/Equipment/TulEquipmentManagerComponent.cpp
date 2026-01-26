// Fill out your copyright notice in the Description page of Project Settings.


#include "TulEquipmentManagerComponent.h"
#include "TulEquipmentDefinition.h"
#include "TulEquipmentInstance.h"

UTulEquipmentInstance* FTulEquipmentList::AddEntry(TSubclassOf<UTulEquipmentDefinition> EquipmentDefinition)
{
    UTulEquipmentInstance* Result = nullptr;
    check(EquipmentDefinition != nullptr);
    check(OwnerComponent);
    check(OwnerComponent->GetOwner()->HasAuthority());

    // EquipmentDefinition의 멤버 변수들은 EditDefaultsOnly로 정의되어 있어 GetDefault로 들고 와도 우리에게 필요한 것들이 모두 있다
    const UTulEquipmentDefinition* EquipmentCDO = GetDefault<UTulEquipmentDefinition>(EquipmentDefinition);

    TSubclassOf<UTulEquipmentInstance> InstanceType = EquipmentCDO->InstanceType;
    if (!InstanceType)
    {
        InstanceType = UTulEquipmentInstance::StaticClass();
    }

    // Entries에 추가해주자
    FTulAppliedEquipmentEntry& NewEntry = Entries.AddDefaulted_GetRef();
    NewEntry.EquipmentDefinition = EquipmentDefinition;
    NewEntry.Instance = NewObject<UTulEquipmentInstance>(OwnerComponent->GetOwner(), InstanceType);
    Result = NewEntry.Instance;

    // ActorsToSpawn을 통해, Actor들을 인스턴스화 해주자
    // - 어디에? EquipmentInstance에!
    Result->SpawnEquipmentActors(EquipmentCDO->ActorsToSpawn);

    return Result;
}

void FTulEquipmentList::RemoveEntry(UTulEquipmentInstance* Instance)
{
    //  단순히 그냥 Entries를 순회하며, Instance를 찾아서
    for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
    {
        FTulAppliedEquipmentEntry& Entry = *EntryIt;
        if (Entry.Instance == Instance)
        {
            // Actor 제거 작업 및 iterator를 통한 안전하게 Array에서 제거 진행
            Instance->DestroyEquipmentActors();
            EntryIt.RemoveCurrent();
        }
    }
}

UTulEquipmentManagerComponent::UTulEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer), EquipmentList(this)
{
}

UTulEquipmentInstance* UTulEquipmentManagerComponent::EquipItem(TSubclassOf<UTulEquipmentDefinition> EquipmentDefinition)
{
    UTulEquipmentInstance* Result = nullptr;
    if (EquipmentDefinition)
    {
        Result = EquipmentList.AddEntry(EquipmentDefinition);
        if (Result)
        {
            Result->OnEquipped();
        }
    }
    return Result;
}

void UTulEquipmentManagerComponent::UnequipItem(UTulEquipmentInstance* ItemInstance)
{
    if (ItemInstance)
    {
         // 해당 함수는 BP의 Event 노드를 호출해준다 (자세한건 해당 함수 구현하면서 보자)
        ItemInstance->OnUnequipped();
        // EquipmentList에 제거해준다:
        // - 제거하는 과정을 통해 추가되었던  Actor Instance를 제거를 진행한다
        EquipmentList.RemoveEntry(ItemInstance);
    }
}
