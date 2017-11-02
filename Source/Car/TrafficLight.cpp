// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficLight.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "CarPawn.h"


// Sets default values
ATrafficLight::ATrafficLight()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	CollisionComp->bGenerateOverlapEvents = true;
	CollisionComp->SetCollisionProfileName("OverlapAllDynamic");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ATrafficLight::OnOverlapBegin);
	RootComponent = CollisionComp;

	//FActorSpawnParameters params;
	//UStaticMeshComponent* GetStaticMeshComponent();
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

// Called when the game starts or when spawned
void ATrafficLight::BeginPlay()
{
	Super::BeginPlay();
	CountTime();
}

// Called every frame
void ATrafficLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (LightColor == 1) {
		Mesh->SetStaticMesh(RedLight);
	}
	else if (LightColor == 2) {
		Mesh->SetStaticMesh(YellowLight);
	}
	else if (LightColor == 3) {
		Mesh->SetStaticMesh(GreenLight);
	}
}

UBoxComponent * ATrafficLight::GetCollisionComp()
{
	return CollisionComp;
}

void ATrafficLight::CountTime()
{
	GetWorldTimerManager().SetTimer(ChangeColorTimer, this, &ATrafficLight::ChangeColor, 2.0f, false);
}

UStaticMeshComponent * ATrafficLight::GetStaticMeshComponent()
{
	return Mesh;
}

void ATrafficLight::ChangeColor()
{
	LightColor++;
	if (LightColor > 3) {
		LightColor = 1;
	}
	CountTime();
}

void ATrafficLight::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
	CarPawn->CheckLightColor(LightColor);

}
