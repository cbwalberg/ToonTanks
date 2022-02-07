// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh; 
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")); 
	ProjectileMovementComp -> MaxSpeed = 1300.f;
	ProjectileMovementComp -> InitialSpeed = 1300.f; 
	
	TrailParticlesComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles Component"));
	TrailParticlesComponent -> SetupAttachment(ProjectileMesh); }

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();
	// When this object hits another component call &AProjectile::OnHit
	ProjectileMesh -> OnComponentHit.AddDynamic(this, &AProjectile::OnHit); 
	if (LaunchSound) {
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation()); } }

void AProjectile::OnHit(UPrimitiveComponent* HitComp,  AActor* OtherActor,  UPrimitiveComponent* OtherComp,  FVector NormalImpulse, const FHitResult& Hit) {
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr) return;
	if (OtherActor && OtherActor != this && OtherActor != MyOwner) { // Ensure OtherActor exists and that Projectile doesn't collide with itself 
		// Using basic damage so passing empty, default UDamageType class	
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwner -> GetInstigatorController(), this, UDamageType::StaticClass()); 
		if (HitSound) {
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation()); }

		if (HitParticles) {
			// Creates particle effect	
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation()); }
		
		if (HitCameraShakeClass) {
			GetWorld() -> GetFirstPlayerController() -> ClientStartCameraShake(HitCameraShakeClass); } }
	
	// Destroys this object
	Destroy(); }
