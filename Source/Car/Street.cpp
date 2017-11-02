// Fill out your copyright notice in the Description page of Project Settings.

#include "Street.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "CarPawn.h"
#include "Checkpointer.h"

// Sets default values
AStreet::AStreet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AStreet::OnOverlapBegin);
	RootComponent = CollisionComp;

	/*CP = CreateDefaultSubobject<UChildActorComponent>("CP");
	CP->SetChildActorClass(ACheckpointer::StaticClass());
	CP->CreateChildActor()*/;
}

// Called when the game starts or when spawned
void AStreet::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AStreet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent * AStreet::GetCollisionComp()
{
	return CollisionComp;
}

void AStreet::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
	CarPawn->ChangeSpeedRule(MaxSpeedAllowed);

}

