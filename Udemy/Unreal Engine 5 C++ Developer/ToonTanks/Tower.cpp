// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
// #include "DrawDebugHelpers.h"

ATower::ATower()
{
    LaserPointer = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Laser Pointer"));
	LaserPointer->SetupAttachment(TurretMesh);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle,
        this,
        &ATower::CheckFireCondition,
        FireRate,
        true
    );
}

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    
    if (InFireRange() && IsTankInSight())
        RotateTurret(Tank->GetActorLocation());
    
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
    Destroy();
}

void ATower::CheckFireCondition()
{
    if (Tank && Tank->bAlive && InFireRange() && IsTankInSight()) {
        Fire();
    }
        
}

bool ATower::InFireRange()
{
    return (
        Tank
        && FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange
    );
}

bool ATower::IsTankInSight()
{
    FHitResult HitResult;
    FVector Start = LaserPointer->GetComponentLocation();
	FVector End = Tank->GetActorLocation();
    // DrawDebugLine(GetWorld(), Start, End, FColor::Green, false);
    // DrawDebugPoint(GetWorld(), FEnd, 1.f, FColor::Green, false);
    FCollisionShape Sphere = FCollisionShape::MakeSphere(10.f);

    bool hasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
    );
    AActor* HitActor = HitResult.GetActor();
    return HitActor && HitActor == Tank;
}