// Fill out your copyright notice in the Description page of Project Settings.


#include "TulExperienceActionSet.h"
#include "GameFeatureAction.h"

UTulExperienceActionSet::UTulExperienceActionSet()
{
}

#if WITH_EDITORONLY_DATA
void UTulExperienceActionSet::UpdateAssetBundleData()
{
	Super::UpdateAssetBundleData();

	for (UGameFeatureAction* Action : Actions)
	{
		if (Action)
		{
			Action->AddAdditionalAssetBundleData(AssetBundleData);
		}
	}
}
#endif
