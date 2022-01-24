// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();

protected:
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	/* "UPROPERTY" takes various arguments to modify variable metadata
	 * "VisibleAnywhere" and "BluePrintReadOnly" allow the var to be viewed in the project editor and 
	 * blueprint event graph respectively. "meta" is an object for additional params, "AllowPrivateAccess"
	 * is a param allowing blueprint event graph access to a private var 
	 *
	 * "class" forward declares any class not in #include section, 
	 * though required to be #included in .cpp file. Minizimes #includes in .h files
	 */  
 
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Combat") 
	TSubclassOf<class AProjectile> ProjectileClass; };
