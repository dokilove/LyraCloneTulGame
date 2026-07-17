// Fill out your copyright notice in the Description page of Project Settings.


#include "TulInventoryItemInstance.h"
#include "TulInventoryItemDefinition.h"

UTulInventoryItemInstance::UTulInventoryItemInstance(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

const UTulInventoryItemFragment* UTulInventoryItemInstance::FindFragmentByClass(TSubclassOf<UTulInventoryItemFragment> FragmentClass) const
{
    if ((ItemDef != nullptr) && (FragmentClass != nullptr))
    {
        // TulIInventoryItemDefinition은 모든 멘버 변수가 EditDefaultsOnly로 선언되어 있으므로,  GetDefault로 가져와도 무관하다
        // - Fragment 정보는  Instance가 아닌 Definition에 있다
        return GetDefault<UTulInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
    }
    return nullptr;
}

void UTulInventoryItemInstance::AddStatTagStack(FGameplayTag Tag, int32 StackCount)
{
    StatTags.AddStack(Tag, StackCount);
}

void UTulInventoryItemInstance::RemoveStatTagStack(FGameplayTag Tag, int32 StackCount)
{
    StatTags.RemoveStack(Tag, StackCount);
}

bool UTulInventoryItemInstance::HasStatTag(FGameplayTag Tag) const
{
    return StatTags.ContainsTag(Tag);
}

int32 UTulInventoryItemInstance::GetStatTagStackCount(FGameplayTag Tag) const
{
    return StatTags.GetStackCount(Tag);
}
