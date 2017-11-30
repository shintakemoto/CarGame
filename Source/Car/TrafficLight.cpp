// Fill out your copyright notice in the Description page of Project Settings.

#include "TrafficLight.h"
#include "Engine/World.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "CarPawn.h"
#include "TP_ThirdPerson/TP_ThirdPersonCharacter.h"

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
	if (LightColor >= 1 && LightColor <= 5) {
		Mesh->SetStaticMesh(RedLight);
	}
	else if (LightColor > 5 && LightColor <= 9) {
		Mesh->SetStaticMesh(GreenLight);
		if (CarNPC != nullptr) {
			CarNPC->KeepMoving();
			//UE_LOG(LogTemp, Warning, TEXT("GO"));
		}
	}
	else if (LightColor == 10) {
		Mesh->SetStaticMesh(YellowLight);
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

int32 ATrafficLight::GetLightColor()
{
	return LightColor;
}

void ATrafficLight::ChangeColor()
{
	LightColor++;
	if (LightColor > 10) {
		LightColor = 1;
	}
	
	CountTime();
}


void ATrafficLight::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor != nullptr && OtherActor->IsA(ACarPawn::StaticClass())) {
		ACarPawn* CarPawn = Cast<ACarPawn>(OtherActor);
		CarPawn->CheckLightColor(LightColor);
	}
	if (OtherActor != nullptr && OtherActor->IsA(ATP_ThirdPersonCharacter::StaticClass())) {
		ATP_ThirdPersonCharacter* ThirdPerson = Cast<ATP_ThirdPersonCharacter>(OtherActor);
		CarNPC = ThirdPerson;
		if (LightColor <= 5) {
			CarNPC->StopMoving();
			UE_LOG(LogTemp, Warning, TEXT("STOP"));
		}
		else {
			CarNPC->KeepMoving();
			//UE_LOG(LogTemp, Warning, TEXT("GO"));
		}
	}
}

void ATrafficLight::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != nullptr && OtherActor->IsA(ATP_ThirdPersonCharacter::StaticClass())) {
		ATP_ThirdPersonCharacter* ThirdPerson = Cast<ATP_ThirdPersonCharacter>(CarNPC);
		ThirdPerson = nullptr;
	}
}