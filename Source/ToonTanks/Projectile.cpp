// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh; 
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component")); 
	ProjectileMovementComp -> MaxSpeed = 1300.f;
	ProjectileMovementComp -> InitialSpeed = 1300.f; }

// Called when the game starts or when spawned
void AProjectile::BeginPlay() {
	Super::BeginPlay();
	// When this object hits another component call &AProjectile::OnHit
	ProjectileMesh -> OnComponentHit.AddDynamic(this, &AProjectile::OnHit); }

void AProjectile::OnHit(UPrimitiveComponent* HitComp,  AActor* OtherActor,  UPrimitiveComponent* OtherComp,  FVector NormalImpulse, const FHitResult& Hit) {
	if (GetOwner() == nullptr) return;
	if (OtherActor && OtherActor != this && OtherActor != GetOwner()) { // Ensure OtherActor exists and that Projectile doesn't collide with itself 
		// Using basic damage so passing empty, default UDamageType class	
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			GetOwner() -> GetInstigatorController(),
			this,
			UDamageType::StaticClass()); 
		
		// Destroys this object
		Destroy(); } }
