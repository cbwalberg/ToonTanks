// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	float Damage = 50.f;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, BluePrintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* TrailParticlesComponent; 
	
	// Since this callback function is bound to the OnComponentHit delegate, it must take this exact function signiture
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit); };
