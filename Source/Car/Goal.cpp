// Fill out your copyright notice in the Description page of Project Settings.

#include "Goal.h"
#include "Components/BoxComponent.h"
#include "CarPawn.h"

// Sets default values
AGoal::AGoal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AGoal::OnOverlapBegin);
	RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void AGoal::BeginPlay()
{
	Super::BeginPlay();
	Number = 0;
}

// Called every frame
void AGoal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent * AGoal::GetCollisionComp()
{
	return CollisionComp;
}

int AGoal::GetNumber()
{
	return Number;
}

void AGoal::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(ACarPawn::StaticClass())) {
		ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
		CarPawn->Score();
		Number++;
	}
}