// Fill out your copyright notice in the Description page of Project Settings.


#include "TulTaggedActor.h"

// Sets default values
ATulTaggedActor::ATulTaggedActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATulTaggedActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATulTaggedActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

