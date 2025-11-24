// Fill out your copyright notice in the Description page of Project Settings.


#include "TulPawnComponent_CharacterParts.h"
#include "GameFramework/Character.h"

UTulPawnComponent_CharacterParts::UTulPawnComponent_CharacterParts(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

USkeletalMeshComponent* UTulPawnComponent_CharacterParts::GetParentMeshComponent() const
{
    // Character를 활용하여 최상위 SkeletalMesh를 반환한다
    if (AActor* OwnerActor = GetOwner())
    {
        if (ACharacter* OwningCharacter = Cast<ACharacter>(OwnerActor))
        {
            if (USkeletalMeshComponent* MeshComponent = OwningCharacter->GetMesh())
            {
                return MeshComponent;
            }
        }
    }
    return nullptr;
}

USceneComponent* UTulPawnComponent_CharacterParts::GetSceneComponentToAttachTo() const
{
    // Parent에 SkeletalMeshComponent가 있으면 반환학소
    if (USkeletalMeshComponent* MeshComponent = GetParentMeshComponent())
    {
        return MeshComponent;
    }

    // 그리고 RootComponent도 확인하고
    if (AActor* OwnerActor = GetOwner())
    {
        return OwnerActor->GetRootComponent();
    }

    // 그냥 nullptr 반환
    return nullptr;
}

void UTulPawnComponent_CharacterParts::BroadcastChanged()
{
}

FTulCharacterPartHandle UTulPawnComponent_CharacterParts::AddCharacterPart(const FTulCharacterPart& NewPart)
{
    return CharacterPartList.AddEntry(NewPart);
}

bool FTulCharacterPartList::SpawnActorForEntry(FTulAppliedCharacterPartEntry& Entry)
{
    bool bCreatedAnyActor = false;

    // 전달된 AppliedCharacterPartEntry의 Part Class가 제대로 세팅되어 있다면
    if (Entry.Part.PartClass != nullptr)
    {
        // OwnerComponent의 Owner에 속한 World를 반환
        UWorld* World = OwnerComponent->GetWorld();

        // TulPawnComponent_CharacterParts에 어느 Component에 붙일 것인지 결정한다
        // - GetSceneComponentToAttachTo
        if (USceneComponent* ComponentToAttachTo = OwnerComponent->GetSceneComponentToAttachTo())
        {
            // 붙일 Component인 ComponentToAttachTo의 Bone 혹은 SocketName을 통해 어디에 붙일지 Transform을 계산한다
            const FTransform SpawnTranform = ComponentToAttachTo->GetSocketTransform(Entry.Part.SocketName);

            // 우리는 Actor-Actor의 결합이므로, ChildActorComponent를 활용한다
            UChildActorComponent* PartComponent = NewObject<UChildActorComponent>(OwnerComponent->GetOwner());
            PartComponent->SetupAttachment(ComponentToAttachTo, Entry.Part.SocketName);
            PartComponent->SetChildActorClass(Entry.Part.PartClass);
            // 참고로 RegisterComponent를 통해 마지막으로 RenderWorld인 FScene에 변경내용을 전달한다 (혹은 생성한다)
            PartComponent->RegisterComponent();

            // ChildActorComponent에서 생성한 Actor를 반환하여
            if (AActor* SpawnedActor = PartComponent->GetChildActor())
            {
                // 해당 Actor가 Parent인 TulPawnComponent_CharacterParts의 Owner Actor보가 먼저 Tick이 실행되지 않도록 선행조건을 붙인다
                if (USceneComponent* SpawnedRootComponent = SpawnedActor->GetRootComponent())
                {
                    SpawnedRootComponent->AddTickPrerequisiteComponent(ComponentToAttachTo);
                }
            }
            Entry.SpawnedComponent = PartComponent;
            bCreatedAnyActor = true;
        }
    }

    return bCreatedAnyActor;
}

FTulCharacterPartHandle FTulCharacterPartList::AddEntry(FTulCharacterPart NewPart)
{
    // PawnComponent의 CharacterPartList가 PartHandle을 관리하고, 이를 ControllerComponent_CharacterParts에 전달한다
    FTulCharacterPartHandle Result;
    Result.PartHandle = PartHandleCounter++;

    // Authority가 있다면, AppliedCharacterPartEntry를 Entries에 추가한다
    if (ensure(OwnerComponent && OwnerComponent->GetOwner() && OwnerComponent->GetOwner()->HasAuthority()))
    {
        FTulAppliedCharacterPartEntry& NewEntry = Entries.AddDefaulted_GetRef();
        NewEntry.Part = NewPart;
        NewEntry.PartHandle = Result.PartHandle;

        // 여기서 실제 Actor를 생성하고, OwnerComponent의 Owner Actor에 Actor끼리 RootComponent로 Attach 시킨다
        if (SpawnActorForEntry(NewEntry))
        {
            // BroadcastChanged를 통해, OwnerComponent에서 Owner의 SkeletalMeshComponent를 활용하여, Animation 및 Physisc를 Re-initialize 시킨다?
            OwnerComponent->BroadcastChanged();
        }
    }

    return Result;
}
