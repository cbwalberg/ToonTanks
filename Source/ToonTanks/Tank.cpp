// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATank::ATank()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // Component creation, naming, and object hierarchy attachment
    SpringArmRef = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArmRef -> SetupAttachment(RootComponent);

    CameraRef = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraRef -> SetupAttachment(SpringArmRef);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    // Cast APawn::GetController() return val from AController* to APlayerController*
    PlayerControllerRef = Cast<APlayerController>(GetController());
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // "MoveForward" and "Turn" string vals must == vals in Project Settings > Input > Axis Mappings
    PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent -> BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Verify PlayerControllerRef != null
    if (PlayerControllerRef)
    {
        // GetHitResultUnderCursor() assigns val to the OUT var OUT_MouseHitResult
        // on ECollisionChannel ECC_Visibility with complex tracing = false for performance
        FHitResult OUT_MouseHitResult;
        PlayerControllerRef -> GetHitResultUnderCursor(ECC_Visibility, false, OUT_MouseHitResult);

        // DEV CODE: Visual indication of point where mouse cursor collides with objects on ECC_Visibility channel
        DrawDebugSphere(
            GetWorld(), 
            OUT_MouseHitResult.ImpactPoint,
            15.f,
            12,
            FColor::Red,
            false
        );    
    }

}

// Called on 'W' & 'S' key input
void ATank::Move(float MoveInput)
{
    // UGameplayStatics::GetWorldDeltaSeconds(this) == Delta time
    FVector DeltaLocation(
        MoveInput*MoveSpeed*UGameplayStatics::GetWorldDeltaSeconds(this), 0.f, 0.f
    );

    // Moves this object's RootComponent from current pos to DeltaLocation, collision sweeping = true
    AddActorLocalOffset(DeltaLocation, true);
}

// Called on 'A' & 'D' key input
void ATank::Turn(float TurnInput)
{
    // UGameplayStatics::GetWorldDeltaSeconds(this) == Delta time
    FRotator DeltaRotation(
        0.f, TurnInput*TurnSpeed*UGameplayStatics::GetWorldDeltaSeconds(this), 0.f
    );

    // Rotates this object's RootComponent by DeltaComponent around its local axes, collision sweeping = true
    AddActorLocalRotation(DeltaRotation, true); 
}
