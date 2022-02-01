// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Turret.h"

#include "Kismet/GameplayStatics.h"

// Protected
void AToonTanksGameMode::BeginPlay() {
    Super::BeginPlay();
    HandleGameStart(); }

// Private
void AToonTanksGameMode::HandleGameStart() {
    TargetTurrets = GetTargetTurretCount();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); 
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0)); 

    StartGame(); // BlueprintImplementableEvent
    
    if (ToonTanksPlayerController) {
        ToonTanksPlayerController -> SetPlayerEnabledState(false);

        // Set up a timer that executes a function that expects parameters using FTimerDelegate object 
        FTimerHandle PlayerEnableTimerHandle; 
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true);

        GetWorldTimerManager().SetTimer(
            PlayerEnableTimerHandle, 
            PlayerEnableTimerDelegate, 
            StartDelay, 
            false); } }


int32 AToonTanksGameMode::GetTargetTurretCount() {
    TArray<AActor*> Turrets;
    // ~::StaticClass returns a UClass representing a C++ class 
    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), Turrets);
    return Turrets.Num(); }


// Public
void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
    if (DeadActor == Tank) {
        Tank -> HandleDestruction();
        GameOver(false); // false: game lost
        if (ToonTanksPlayerController) {
            ToonTanksPlayerController -> SetPlayerEnabledState(false); } }
    else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor)) {
        DestroyedTurret -> HandleDestruction(); 
        TargetTurrets--; 
        if (TargetTurrets == 0)
            GameOver(true); /* true: game won */ } }
