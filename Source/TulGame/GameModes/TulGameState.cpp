// Fill out your copyright notice in the Description page of Project Settings.


#include "TulGameState.h"
#include "TulExperienceManagerComponent.h"

ATulGameState::ATulGameState()
{
	ExperienceManagerComponent = CreateDefaultSubobject<UTulExperienceManagerComponent>(TEXT("ExperienceManagerComponent"));
}
