// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Turret.h"

#include "Kismet/GameplayStatics.h"


void AToonTanksGameMode::BeginPlay() {
    Super::BeginPlay();
    HandleGameStart(); }


void AToonTanksGameMode::HandleGameStart() {
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


void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
    if (DeadActor == Tank) {
        Tank -> HandleDestruction();
        if (ToonTanksPlayerController) {
            ToonTanksPlayerController -> SetPlayerEnabledState(false); } }
    else if (ATurret* DestroyedTurret = Cast<ATurret>(DeadActor)) {
        DestroyedTurret -> HandleDestruction(); } }
