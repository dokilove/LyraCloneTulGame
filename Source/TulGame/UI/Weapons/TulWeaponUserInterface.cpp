// Fill out your copyright notice in the Description page of Project Settings.


#include "TulWeaponUserInterface.h"
#include "TulGame/Equipment/TulEquipmentManagerComponent.h"
#include "TulGame/Weapons/TulWeaponInstance.h"

UTulWeaponUserInterface::UTulWeaponUserInterface(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
}

void UTulWeaponUserInterface::NativeTick(const FGeometry& MyGeoMetry, float InDeltaTime)
{
	Super::NativeTick(MyGeoMetry, InDeltaTime);

	// Pawn을 가져오고
	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		// EquipmentManagerComponent를 활용하여, WaeponInstance를 가져오자
		if (UTulEquipmentManagerComponent* EquipmentManager = Pawn->FindComponentByClass<UTulEquipmentManagerComponent>())
		{
			if (UTulWeaponInstance* NewInstance = EquipmentManager->GetFirstInstanceOfType<UTulWeaponInstance>())
			{
				if (NewInstance != CurrentInstance && NewInstance->GetInstigator() != nullptr)
				{
					// 새로 업데이트해주고, OnWeaponChanged 호출 진행
					UTulWeaponInstance* OldWeapon = CurrentInstance;
					CurrentInstance = NewInstance;
					OnWeaponChanged(OldWeapon, CurrentInstance);
				}
			}
		}
	}
}
