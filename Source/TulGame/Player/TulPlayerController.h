// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularPlayerController.h"
#include "TulPlayerController.generated.h"

class UTulAbilitySystemComponent;
class ATulPlayerState;

/**
 * 
 */
UCLASS()
class TULGAME_API ATulPlayerController : public AModularPlayerController
{
	GENERATED_BODY()
	
public:
	ATulPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/**
	* Player Controller interface
	*/
	virtual void PostProcessInput(const float DeltaTime, const bool bGamePaused) override;

	/**
	* member methods
	*/
	ATulPlayerState* GetTulPlayerState() const;
	UTulAbilitySystemComponent* GetTulAbilitySystemComponent() const;
};
