// Fill out your copyright notice in the Description page of Project Settings.

#include "Street.h"


// Sets default values
AStreet::AStreet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStreet::BeginPlay()
{
	Super::BeginPlay();
	MaxSpeedAllowed = 20.f;
}

// Called every frame
void AStreet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

