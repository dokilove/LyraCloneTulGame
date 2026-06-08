#include "TulReticleWidgetBase.h"
#include "TulGame/Weapons/TulWeaponInstance.h"
#include "TulGame/Inventory/TulInventoryItemInstance.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(TulReticleWidgetBase)

UTulReticleWidgetBase::UTulReticleWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UTulReticleWidgetBase::InitializeFromWeapon(UTulWeaponInstance* InWeapon)
{
	WeaponInstance = InWeapon;
	InventoryInstance = nullptr;
	if (WeaponInstance)
	{
		InventoryInstance = Cast<UTulInventoryItemInstance>(WeaponInstance->GetInstigator());
	}
}
