// Fill out your copyright notice in the Description page of Project Settings.

#include "Checkpointer.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Street.h"
#include "CarPawn.h"

// Sets default values
ACheckpointer::ACheckpointer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ACheckpointer::OnOverlapBegin);
	RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void ACheckpointer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent * ACheckpointer::GetCollisionComp()
{
	return CollisionComp;
}

int32 ACheckpointer::GetIndex()
{
	return Index;
}

void ACheckpointer::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(ACarPawn::StaticClass())) {
		ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
		CarPawn->CheckDirection(Index);
	}
}
