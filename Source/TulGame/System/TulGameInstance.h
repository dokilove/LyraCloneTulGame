// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TulGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TULGAME_API UTulGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	/**
	* UGameInstance's interface
	*/
	virtual void Init() override;
	virtual void Shutdown() override;
};
