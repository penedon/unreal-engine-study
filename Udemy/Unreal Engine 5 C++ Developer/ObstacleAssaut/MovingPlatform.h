// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAUT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
	public:	
		// Sets default values for this actor's properties
		AMovingPlatform();

	protected:
		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void Tick(float DeltaTime) override;

	private:
		
		UPROPERTY(EDitAnywhere, Category="Moving")
		FVector PlatformVelocity = FVector(0, 0, 0);

		UPROPERTY(EDitAnywhere, Category="Moving")
		float MaxMovedDistance = 1000;

		UPROPERTY(EDitAnywhere, Category="Rotating")
		FRotator RotationVelocity;

		FVector StartLocation;

		void MovePlatform(float DeltaTime);
		void RotatePlatform(float DeltaTime);
		bool ShouldPlatformReturn() const;
		float GetDistanceMoved() const;
};
