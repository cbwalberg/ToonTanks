// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

UCLASS()
class TOONTANKS_API ATank : public ABasePawn {
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	APlayerController* TankPlayerController;
	
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	float MoveSpeed = 200.f;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, meta = (AllowPrivateAccess = "true"))
	float TurnSpeed = 50.f;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmRef;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraRef;

	void MoveForward(float MoveForwardInput);
	void MoveRight(float MoveRightInput); };
