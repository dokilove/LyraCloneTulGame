// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ModularCharacter.h"
#include "AbilitySystemInterface.h"
#include "TulCharacter.generated.h"

class UTulPawnExtensionComponent;
class UTulCameraComponent;
class UTulHealthComponent;

UCLASS()
class TULGAME_API ATulCharacter : public AModularCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATulCharacter();

	void OnAbilitySystemInitialized();
	void OnAbilitySystemUninitialized();

	/**
	* IAbilitySystemInterface
	*/
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tul|Character")
	TObjectPtr<UTulPawnExtensionComponent> PawnExtComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tul|Character")
	TObjectPtr<UTulCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tul|Character")
	TObjectPtr<UTulHealthComponent> HealthComponent;
};
