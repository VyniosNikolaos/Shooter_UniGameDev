// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BurningFireEmitter.generated.h"

// Forward Declarations
class USphereComponent;
class UNiagaraComponent;
class AShooterCharacter;
class USoundBase;
class UAudioComponent;


UCLASS()
class SHOOTER_API ABurningFireEmitter : public AActor
{
	GENERATED_BODY()

public:
	ABurningFireEmitter();

protected:
	virtual void BeginPlay() override;

	// Handle overlap event
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
						UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
						bool bFromSweep, const FHitResult& SweepResult);

private:

	//static mesh for the plate
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Burning", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* FireMesh;
	
	// Collision box
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BurningFire", meta = (AllowPrivateAccess = "true"))
	USphereComponent* CollisionSphere;

	// Niagara System for fire visuals
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BurningFire", meta = (AllowPrivateAccess = "true"))
	UNiagaraComponent* FireEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BurningFire", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "BurningFire", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* FireAudioComponent;
	
	// Damage applied to the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BurningFire", meta = (AllowPrivateAccess = "true"))
	float BurnDamage = 10.0f;

};

