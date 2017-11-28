// Fill out your copyright notice in the Description page of Project Settings.

#include "Sidewalk.h"
#include "Components/BoxComponent.h"
#include "CarPawn.h"

// Sets default values
ASidewalk::ASidewalk()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASidewalk::OnOverlapBegin);
	RootComponent = CollisionComp;
}

// Called when the game starts or when spawned
void ASidewalk::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASidewalk::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent * ASidewalk::GetCollisionComp()
{
	return CollisionComp;
}

void ASidewalk::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(ACarPawn::StaticClass())) {
		ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
		CarPawn->InSidewalk();
	}
}