// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
// #include "DrawDebugHelpers.h"

// Sets default values
ABasePawn::ABasePawn() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Component creation, naming, and object hierarchy attachment
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh -> SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh -> SetupAttachment(BaseMesh);

	ProjectileSpawn = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn"));
	ProjectileSpawn -> SetupAttachment(TurretMesh); }

void ABasePawn::HandleDestruction() {
	// Visual/Sound effects on death
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathEffect, GetActorLocation(), GetActorRotation()); }

void ABasePawn::RotateTurret(FVector LookAtTarget) {
	FVector ToTarget = LookAtTarget - TurretMesh -> GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	TurretMesh -> SetWorldRotation(LookAtRotation); }

void ABasePawn::Fire() {
	// Draw Sphere at Projectile Spawn Point
	// DrawDebugSphere(GetWorld(), ProjectileSpawn -> GetComponentLocation(), 25.f, 12, FColor::Red, false, 3.f); 

	// "auto" allows compiler to determine type
	auto Projectile = GetWorld() -> SpawnActor<AProjectile>(
		ProjectileClass, 
		ProjectileSpawn -> GetComponentLocation(), 
		ProjectileSpawn -> GetComponentRotation()); 
	Projectile -> SetOwner(this); }
