// Fill out your copyright notice in the Description page of Project Settings.

#include "AiCar.h"


// Sets default values
AAiCar::AAiCar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAiCar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAiCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

