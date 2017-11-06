// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sidewalk.generated.h"

UCLASS()
class CAR_API ASidewalk : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASidewalk();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UBoxComponent* GetCollisionComp();
	
private:
	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};