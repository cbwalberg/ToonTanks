// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"
#include "Tank.h"

#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATurret::BeginPlay() {
    Super::BeginPlay();

    // Get player and cast
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

    // true param is for looping
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATurret::CheckFireCondition, FireRate, true); }


void ATurret::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (InFireRange()) RotateTurret(Tank -> GetActorLocation()); }


void ATurret::CheckFireCondition() {
    if (InFireRange()) Fire(); }


bool ATurret::InFireRange() {
    if (Tank) {
        // FVector::Dist() returns location between two Actors
        float Distance = FVector::Dist(GetActorLocation(), Tank -> GetActorLocation());
        if (Distance <= FireRange) return true; }

    return false; }
