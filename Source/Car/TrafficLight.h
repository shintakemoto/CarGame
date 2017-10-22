// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrafficLight.generated.h"

UCLASS()
class CAR_API ATrafficLight : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrafficLight();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	class UBoxComponent* GetCollisionComp();

	void ChangeColor();
	void CountTime();
	UStaticMeshComponent* GetStaticMeshComponent();
	FTimerHandle ChangeColorTimer;

	
private:


	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* RedLight;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* YellowLight;
	UPROPERTY(EditAnywhere)
		class UStaticMesh* GreenLight;
	UPROPERTY(EditAnywhere)
		int32 LightColor;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* CollisionComp;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


};
